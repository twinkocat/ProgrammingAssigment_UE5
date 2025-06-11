// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUpItem.h"
#include "Features/Interaction/InteractableComponent.h"
#include "Features/Inventory/IInventoryComponent.h"
#include "Features/Inventory/InventoryComponent.h"


APickUpItem::APickUpItem(): CountToAdd(0), InteractionType()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

bool APickUpItem::IsInteractable_Implementation(UInteractableComponent* Component) const
{
	return true;
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
	return Success;
}

void APickUpItem::StartLooking_Implementation(UInteractableComponent* Component)
{
}


void APickUpItem::StopLooking_Implementation(UInteractableComponent* Component)
{
}

