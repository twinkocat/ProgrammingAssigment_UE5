// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Inventory/InventoryComponent.h"

#include "GameplayTagContainer.h"
#include "Features/Inventory/InventoryDataAsset.h"
#include "Features/Inventory/InventoryItem.h"


UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
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
		
		for (FInventoryItemWrapper& Element : Items)
		{
			if (Element.Item && Element.Tag == ItemTag)
			{
				const int OldCount = Element.Count;
				Element.Count = FMath::Clamp(Element.Count + ItemCount, 0, ItemData.MaxInStack);
				UE_LOG(LogTemp, Log, TEXT("Updated item '%s': %d -> %d"), *Element.Item->GetItemName().ToString(), OldCount, Element.Count);
				return;
			}
		}
	}

	FInventoryItemWrapper NewWrapper;
	UInventoryItem* NewItem = UInventoryItem::Create(ItemData);

	NewWrapper.Tag = ItemData.Tag;
	NewWrapper.Item = NewItem;
	NewWrapper.Count = FMath::Clamp(ItemCount, 0, ItemData.MaxInStack);
	Items.Add(NewWrapper);

	UE_LOG(LogTemp, Log, TEXT("Added new item '%s' with count: %d"), *NewWrapper.Item->GetItemName().ToString(), NewWrapper.Count);
}

void UInventoryComponent::UseItem(const FGameplayTag& ItemTag)
{
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		FInventoryItemWrapper& Element = Items[i];

		if (Element.Item && Element.Tag == ItemTag)
		{
			if (Element.Item->IsConsumable())
			{
				Element.Count = FMath::Clamp(Element.Count - 1, 0, INT_MAX);
				UE_LOG(LogTemp, Log, TEXT("Used consumable item: %s, remaining count: %d"), *ItemTag.ToString(), Element.Count);
				
				if (Element.Count == 0)
				{
					Items.RemoveAt(i);
					UE_LOG(LogTemp, Log, TEXT("Item %s removed from inventory"), *ItemTag.ToString());
				}
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Used non-consumable item: %s"), *ItemTag.ToString());
			}

			Element.Item->OnUse(this);
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


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}



