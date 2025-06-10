// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"

class UInventoryComponent;
/**
 * 
 */
UCLASS(BlueprintType)
class PROGRAMMINGASSIGMENT_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	void OnUse(UInventoryComponent* InventoryComponent);
	void OnDrop(UInventoryComponent* InventoryComponent);

	FORCEINLINE FText GetItemName() const { return ItemData.Name; };

	FORCEINLINE bool IsConsumable() const { return ItemData.Consumable; }
	
	static UInventoryItem* Create(const FInventoryItemData& ItemData);

protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	FInventoryItemData ItemData;
};
