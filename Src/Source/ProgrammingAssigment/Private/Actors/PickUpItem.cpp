// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUpItem.h"
#include "Features/Interaction/InteractableComponent.h"
#include "Features/Inventory/IInventoryComponent.h"
#include "Features/Inventory/InventoryComponent.h"


APickUpItem::APickUpItem(): CountToAdd(0)
{
	PrimaryActorTick.bCanEverTick = false;
}


bool APickUpItem::StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo)
{
	bool Success = false;
	if (UInventoryComponent* InventoryComponent = IIInventoryComponent::Execute_GetInventoryComponent(Component->GetOwner()))
	{
		InventoryComponent->AddItem(ItemToAdd, CountToAdd);
		Success = true;
	}
	InteractionInfo.SuccessInteract = Success;
	InteractionInfo.InteractionType = InteractionType;

	if (Success)
	{
		Destroy();
	}
	
	return Success;
}
