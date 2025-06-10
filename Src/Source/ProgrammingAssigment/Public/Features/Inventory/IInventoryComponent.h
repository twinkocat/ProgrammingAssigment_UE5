// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInventoryComponent.generated.h"

class UInventoryComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class UIInventoryComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGRAMMINGASSIGMENT_API IIInventoryComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	UInventoryComponent* GetInventoryComponent() const;

	virtual UInventoryComponent* GetInventoryComponent_Implementation() const = 0;
};
