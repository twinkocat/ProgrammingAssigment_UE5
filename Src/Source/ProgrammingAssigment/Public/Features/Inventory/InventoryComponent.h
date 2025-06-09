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
	FGameplayTag Tag;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory", meta=(MultiLine=true))
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory")
	int MaxInStack = 99;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TSoftObjectPtr<UTexture2D> ItemImage;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Inventory")
	TArray<UInventoryItemCommand*> OnUseCommand;
};

USTRUCT(BlueprintType)
struct FInventoryItemWrapper
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	UInventoryItem* Item;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int Count;
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
