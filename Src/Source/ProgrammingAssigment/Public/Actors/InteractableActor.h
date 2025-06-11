// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Features/Interaction/Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

enum EInteractionType : uint8;

UCLASS()
class PROGRAMMINGASSIGMENT_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableActor();
	
	virtual bool IsInteractable_Implementation(UInteractableComponent* Component) const override;
	virtual bool StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo) override;
	virtual void StartLooking_Implementation(UInteractableComponent* Component) override;
	virtual void StopLooking_Implementation(UInteractableComponent* Component) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TEnumAsByte<EInteractionType> InteractionType;
};
