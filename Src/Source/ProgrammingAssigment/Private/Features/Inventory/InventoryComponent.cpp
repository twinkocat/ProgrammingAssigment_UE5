// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Inventory/InventoryComponent.h"

#include "GameplayTagContainer.h"
#include "Actors/PlayersPickUp.h"
#include "Features/Inventory/InventoryDataAsset.h"
#include "Features/Inventory/InventoryItem.h"
#include "Net/UnrealNetwork.h"


UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventoryComponent, Items)
}

void UInventoryComponent::AddItem(const FGameplayTag& ItemTag, const int ItemCount)
{
	FInventoryItemData ItemData;
	
	
	if (InventoryDataAsset.LoadSynchronous()->TryGetInventoryData(ItemTag, ItemData))
	{
		FAddedItemInfo AddedItemInfo;
		AddedItemInfo.Name = ItemData.Name;
		AddedItemInfo.Image = ItemData.ItemImage;
		AddedItemInfo.Count = ItemCount;
		OnItemAdded.Broadcast(AddedItemInfo);

		if (FInventoryItemWrapper* ItemWrapper = FindItem_Internal(ItemTag))
		{
			const int OldCount = ItemWrapper->Count;
			ItemWrapper->Count = FMath::Clamp(ItemWrapper->Count + ItemCount, 0, ItemData.MaxInStack);
			UE_LOG(LogTemp, Log, TEXT("Updated item '%s': %d -> %d"), *ItemWrapper->Item->GetItemName().ToString(), OldCount, ItemWrapper->Count);
			return;
		}
	}

	UInventoryItem* NewItem = UInventoryItem::Create(ItemData);
	FInventoryItemWrapper NewWrapper;
	NewWrapper.Tag = ItemData.Tag;
	NewWrapper.Item = NewItem;
	NewWrapper.Count = FMath::Clamp(ItemCount, 0, ItemData.MaxInStack);
	Items.Add(NewWrapper);

	UE_LOG(LogTemp, Log, TEXT("Added new item '%s' with count: %d"), *NewWrapper.Item->GetItemName().ToString(), NewWrapper.Count);
}

void UInventoryComponent::UseItem(const FGameplayTag& ItemTag)
{
	if (FInventoryItemWrapper* ItemWrapper = FindItem_Internal(ItemTag))
	{
		if (ItemWrapper->Item->IsConsumable())
		{
			RemoveItem_Internal(ItemWrapper, 1);
			UE_LOG(LogTemp, Log, TEXT("Used consumable item: %s, remaining count: %d"), *ItemTag.ToString(), ItemWrapper->Count);
		}
		
		ItemWrapper->Item->OnUse(this);
	}
}

void UInventoryComponent::DropItem(const FGameplayTag& ItemTag, const int ItemCount)
{
	if (FInventoryItemWrapper* ItemWrapper = FindItem_Internal(ItemTag))
	{
		Server_DropItem(*ItemWrapper);
		RemoveItem_Internal(ItemWrapper, ItemCount);
	}
}

void UInventoryComponent::Server_DropItem_Implementation(const FInventoryItemWrapper& ItemWrapper)
{
	const AActor* OwnerActor = GetOwner();
		
	const FVector Positon = OwnerActor->GetActorLocation();
	const FRotator Rotator = GetOwner()->GetActorRotation();
		
	TArray OffsetDirections = { OwnerActor->GetActorForwardVector(), OwnerActor->GetActorRightVector(), -OwnerActor->GetActorRightVector(), -OwnerActor->GetActorForwardVector() };
		
	for (const FVector& Offset : OffsetDirections)
	{
		FVector DropLocation = Positon + Offset * DropDistance;

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(OwnerActor);
		const bool bBlocked = GetWorld()->OverlapAnyTestByChannel(DropLocation,FQuat::Identity, ECC_WorldStatic,FCollisionShape::MakeSphere(DropRadius),TraceParams);

		if (!bBlocked)
		{
			APlayersPickUp* DroppedItem = GetWorld()->SpawnActor<APlayersPickUp>(DroppedItemClass, DropLocation, Rotator);
			DroppedItem->SetupItem(ItemWrapper);
			OnItemDropped.Broadcast();
			break;
		}
	}
}

bool UInventoryComponent::HasItem(const FGameplayTag& ItemTag) const
{
	for (const FInventoryItemWrapper& Element : Items)
	{
		if (Element.Item && Element.Tag == ItemTag)
		{
			return true;
		}
	}
	return false;
}

void UInventoryComponent::RemoveItem(const FGameplayTag& ItemTag, const int ItemCount)
{
	if (FInventoryItemWrapper* Element = FindItem_Internal(ItemTag))
	{
		RemoveItem_Internal(Element, ItemCount);
	}
}

bool UInventoryComponent::FindItem(const FGameplayTag& ItemTag, FInventoryItemWrapper& OutItem) const
{
	if (const FInventoryItemWrapper* Element = FindItem_Internal(ItemTag))
	{
		OutItem = *Element;
		return true;
	}
	return false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

FInventoryItemWrapper* UInventoryComponent::FindItem_Internal(const FGameplayTag& ItemTag) const
{
	const FInventoryItemWrapper* ItemWrapper = Items.FindByPredicate([&](const FInventoryItemWrapper& Element)
	{
		return Element.Item && Element.Tag == ItemTag;
	});
	
	return const_cast<FInventoryItemWrapper*>(ItemWrapper);
}

void UInventoryComponent::RemoveItem_Internal(FInventoryItemWrapper* Item, const int ItemCount)
{
	Item->Count = FMath::Clamp(Item->Count - ItemCount, 0, INT_MAX);

	if (Item->Count == 0)
	{
		const int IndexToRemove = Items.IndexOfByPredicate([&](const FInventoryItemWrapper& Element)
		{
			return Element.Item && Element.Tag == Item->Tag;
		});
		
		Items.RemoveAt(IndexToRemove);
		UE_LOG(LogTemp, Log, TEXT("Item %s removed from inventory"), *Item->Tag.ToString());
	}
}



