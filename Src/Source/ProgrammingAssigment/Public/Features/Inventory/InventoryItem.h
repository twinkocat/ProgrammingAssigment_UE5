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

	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void OnUse(UInventoryComponent* InventoryComponent);
	void OnDrop(UInventoryComponent* InventoryComponent);

	FORCEINLINE FText GetItemName() const { return ItemData.Name; };

	FORCEINLINE bool IsConsumable() const { return ItemData.Consumable; }

	FORCEINLINE FText GetItemDescription() const { return ItemData.Description; };

	FORCEINLINE TSoftObjectPtr<UTexture2D> GetImage() const { return ItemData.ItemImage; };
	
	static UInventoryItem* Create(const FInventoryItemData& ItemData, AActor* Owner);
	static void Dispose(UInventoryItem* InventoryItem, AActor* Owner);
	
protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category="Inventory")
	FInventoryItemData ItemData;
};
