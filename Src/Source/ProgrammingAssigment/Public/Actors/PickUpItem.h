// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InteractableActor.h"
#include "GameFramework/Actor.h"
#include "Features/Interaction/Interactable.h"
#include "PickUpItem.generated.h"

class UInventoryComponent;

enum EInteractionType : uint8;

UCLASS(Blueprintable, BlueprintType)
class PROGRAMMINGASSIGMENT_API APickUpItem : public AInteractableActor
{
	GENERATED_BODY()

public:
	APickUpItem();

	virtual auto GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const -> void override;

	virtual bool StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo) override;

	UFUNCTION(Server, Reliable)
	void Server_SuccessPickup();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnPickup();
	
protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(Categories="Item"))
	FGameplayTag ItemToAdd;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int CountToAdd;
};


