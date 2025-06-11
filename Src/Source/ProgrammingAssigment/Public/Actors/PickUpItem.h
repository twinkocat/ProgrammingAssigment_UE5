// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InteractableActor.h"
#include "GameFramework/Actor.h"
#include "Features/Interaction/Interactable.h"
#include "PickUpItem.generated.h"

enum EInteractionType : uint8;

UCLASS(Blueprintable, BlueprintType)
class PROGRAMMINGASSIGMENT_API APickUpItem : public AInteractableActor
{
	GENERATED_BODY()

public:
	APickUpItem();

	virtual bool StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(Categories="Item"))
	FGameplayTag ItemToAdd;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int CountToAdd;
};


