// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryItem;
class UInventoryDataAsset;
class UInventoryItemCommand;

USTRUCT(BlueprintType)
struct FInventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(Categories="Item"))
	FGameplayTag Tag = FGameplayTag::EmptyTag;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory")
	FText Name = FText::FromString("Item Name");

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory", meta=(MultiLine=true))
	FText Description = FText::FromString("Item Description");

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory")
	int MaxInStack = 99;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TSoftObjectPtr<UTexture2D> ItemImage = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Inventory")
	TArray<UInventoryItemCommand*> OnUseCommand = { };
};

USTRUCT(BlueprintType)
struct FInventoryItemWrapper
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FGameplayTag Tag = FGameplayTag::EmptyTag;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TObjectPtr<UInventoryItem> Item = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int Count = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGRAMMINGASSIGMENT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItem(const FGameplayTag& ItemTag, const int ItemCount);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TArray<FInventoryItemWrapper> Items;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TSoftObjectPtr<UInventoryDataAsset> InventoryDataAsset;
};
