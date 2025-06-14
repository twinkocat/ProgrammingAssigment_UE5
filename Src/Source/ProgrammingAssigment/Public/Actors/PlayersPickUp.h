// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItem.h"
#include "Features/Inventory/InventoryComponent.h"
#include "PlayersPickUp.generated.h"

enum EInteractionType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSetup);

UCLASS(BlueprintType, Blueprintable)
class PROGRAMMINGASSIGMENT_API APlayersPickUp : public APickUpItem
{
	GENERATED_BODY()

public:
	APlayersPickUp();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void SetupItem(const FInventoryItemWrapper& Wrapper);

	UFUNCTION(Server, Reliable)
	void Server_SetupItem(const FInventoryItemWrapper& Wrapper);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_ItemImage();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnItemSetup OnItemSetup;

private:
	void SetupItem_Internal(const FInventoryItemWrapper& Wrapper);
	void ItemWrapperChanged();
	
protected:
	UPROPERTY(ReplicatedUsing=OnRep_ItemImage, BlueprintReadOnly, Category = "Interaction")
	TSoftObjectPtr<UTexture2D> ItemImage;
};
