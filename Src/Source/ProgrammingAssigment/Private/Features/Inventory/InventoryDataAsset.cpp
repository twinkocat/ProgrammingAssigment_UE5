// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Inventory/InventoryDataAsset.h"
#include "Features/Inventory/InventoryComponent.h"

bool UInventoryDataAsset::TryGetInventoryData(const FGameplayTag& TargetTag, FInventoryItemData& ItemData)
{
	for (const FInventoryItemData& Element : InventoryData)
	{
		if (Element.Tag == TargetTag)
		{
			ItemData = Element;
			return true;
		}
	}
	return false;
}
