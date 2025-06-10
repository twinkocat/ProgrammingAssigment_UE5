// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Inventory/InventoryItem.h"
#include "Features/Inventory/InventoryItemCommand.h"


void UInventoryItem::OnUse(UInventoryComponent* InventoryComponent)
{
	for (UInventoryItemCommand* Command : ItemData.OnUseCommand)
	{
		Command->Execute(InventoryComponent);
	}
}

void UInventoryItem::OnDrop(UInventoryComponent* InventoryComponent)
{
}

UInventoryItem* UInventoryItem::Create(const FInventoryItemData& ItemData)
{
	UInventoryItem* NewItem = NewObject<UInventoryItem>();
	NewItem->ItemData = ItemData;
	return NewItem;
}
