// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayersPickUp.h"

#include "Features/Interaction/InteractableComponent.h"
#include "Features/Inventory/IInventoryComponent.h"
#include "Features/Inventory/InventoryComponent.h"


// Sets default values
APlayersPickUp::APlayersPickUp()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayersPickUp::SetupItem_Implementation(const FInventoryItemWrapper& Item)
{
	CurrentItem = Item;
}

bool APlayersPickUp::StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo)
{
	bool Success = false;
	if (UInventoryComponent* InventoryComponent = IIInventoryComponent::Execute_GetInventoryComponent(Component->GetOwner()))
	{
		InventoryComponent->AddItem(CurrentItem.Tag, CurrentItem.Count);
		Success = true;
	}
	InteractionInfo.SuccessInteract = Success;
	InteractionInfo.InteractionType = InteractionType;
	return Success;
}
