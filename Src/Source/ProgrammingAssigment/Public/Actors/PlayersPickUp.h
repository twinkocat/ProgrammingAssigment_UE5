// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Features/Interaction/Interactable.h"
#include "Features/Inventory/InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "PlayersPickUp.generated.h"

enum EInteractionType : uint8;

UCLASS(BlueprintType, Blueprintable)
class PROGRAMMINGASSIGMENT_API APlayersPickUp : public AInteractableActor
{
	GENERATED_BODY()

public:
	APlayersPickUp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void SetupItem(const FInventoryItemWrapper& Item);

	virtual bool StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo) override;
	
protected:
	
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	FInventoryItemWrapper CurrentItem;
};
