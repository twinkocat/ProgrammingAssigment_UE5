// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InventoryDataAsset.generated.h"

struct FInventoryItemData;
/**
 * 
 */
UCLASS()
class PROGRAMMINGASSIGMENT_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FInventoryItemData> InventoryData;
	
	bool TryGetInventoryData(const FGameplayTag& TargetTag, FInventoryItemData& ItemData);
};
