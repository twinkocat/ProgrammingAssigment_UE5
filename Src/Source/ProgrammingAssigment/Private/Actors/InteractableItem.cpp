// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableItem.h"
#include "Features/Interaction/InteractableComponent.h"
#include "Features/Inventory/IInventoryComponent.h"
#include "Features/Inventory/InventoryComponent.h"


AInteractableItem::AInteractableItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AInteractableItem::IsInteractable_Implementation(UInteractableComponent* Component) const
{
	return true;
}

bool AInteractableItem::StartInteract_Implementation(UInteractableComponent* Component)
{
	if (UInventoryComponent* InventoryComponent = IIInventoryComponent::Execute_GetInventoryComponent(Component->GetOwner()))
	{
		InventoryComponent->AddItem(ItemToAdd, CountToAdd);
		return true;
	}
	return false;
}


void AInteractableItem::EndInteract_Implementation(UInteractableComponent* Component)
{
}

void AInteractableItem::StartLooking_Implementation(UInteractableComponent* Component)
{
}


void AInteractableItem::StopLooking_Implementation(UInteractableComponent* Component)
{
}

void AInteractableItem::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	
}

