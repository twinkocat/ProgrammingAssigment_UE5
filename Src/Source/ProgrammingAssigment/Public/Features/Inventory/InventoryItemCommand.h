// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItemCommand.generated.h"

class UInventoryComponent;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew, CollapseCategories)
class PROGRAMMINGASSIGMENT_API UInventoryItemCommand : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void Execute(UInventoryComponent* InventoryComponent);

	virtual void Execute_Implementation(UInventoryComponent* InventoryComponent);
};
