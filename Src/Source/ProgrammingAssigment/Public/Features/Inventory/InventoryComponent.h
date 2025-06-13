// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class APlayersPickUp;
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Inventory")
	bool Consumable = false;

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

USTRUCT(BlueprintType)
struct FAddedItemInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FText Name = FText();

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Image = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int Count = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemDropped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, FAddedItemInfo, Info);



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGRAMMINGASSIGMENT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItem(const FGameplayTag& ItemTag, const int ItemCount);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void UseItem(const FGameplayTag& ItemTag);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void DropItem(const FGameplayTag& ItemTag, const int ItemCount);
	
	UFUNCTION(Server, Reliable)
	void Server_DropItem(const FInventoryItemWrapper& ItemWrapper);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool HasItem(const FGameplayTag& ItemTag) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveItem(const FGameplayTag& ItemTag, const int ItemCount);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool FindItem(const FGameplayTag& ItemTag, FInventoryItemWrapper& OutItem) const;
	
	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnItemDropped OnItemDropped;
	
protected:
	virtual void BeginPlay() override;

private:

	FInventoryItemWrapper* FindItem_Internal(const FGameplayTag& ItemTag) const;
	
	void RemoveItem_Internal(FInventoryItemWrapper* Item, const int ItemCount);

protected:
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Inventory")
	TArray<FInventoryItemWrapper> Items;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TSoftObjectPtr<UInventoryDataAsset> InventoryDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Drop")
	float DropDistance = 50.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Drop")
	float DropRadius = 25.F;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Drop")
	TSubclassOf<APlayersPickUp> DroppedItemClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|Drop")
	TSoftObjectPtr<UAnimMontage> DropAnimMontage;
};
