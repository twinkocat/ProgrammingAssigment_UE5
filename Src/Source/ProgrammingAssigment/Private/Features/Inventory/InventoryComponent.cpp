// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgrammingAssigment/Public/Features/Inventory/InventoryComponent.h"

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
	
	if (InventoryDataAsset.IsValid() && InventoryDataAsset.Get()->TryGetInventoryData(ItemTag, ItemData))
	{
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

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}



