// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItem.h"
#include "Features/Inventory/InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "PlayersPickUp.generated.h"

enum EInteractionType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSetup, FInventoryItemWrapper, ItemWrapper);

UCLASS(BlueprintType, Blueprintable)
class PROGRAMMINGASSIGMENT_API APlayersPickUp : public APickUpItem
{
	GENERATED_BODY()

public:
	APlayersPickUp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void SetupItem(const FInventoryItemWrapper& Item);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_ItemWrapper();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnItemSetup OnItemSetup;
	
protected:
	UPROPERTY(ReplicatedUsing=OnRep_ItemWrapper, BlueprintReadOnly, Category = "Interaction")
	FInventoryItemWrapper ItemWrapper;
};
