// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Features/Interaction/Interactable.h"
#include "InteractableItem.generated.h"

UCLASS()
class PROGRAMMINGASSIGMENT_API AInteractableItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableItem();

protected:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:
	virtual bool IsInteractable_Implementation(UInteractableComponent* Component) const override;
	virtual bool StartInteract_Implementation(UInteractableComponent* Component) override;
	virtual void EndInteract_Implementation(UInteractableComponent* Component) override;
	virtual void StartLooking_Implementation(UInteractableComponent* Component) override;
	virtual void StopLooking_Implementation(UInteractableComponent* Component) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(Categories="Item"))
	FGameplayTag ItemToAdd;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int CountToAdd;
};


