// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUpItem.h"
#include "Features/Interaction/InteractableComponent.h"
#include "Features/Inventory/IInventoryComponent.h"
#include "Features/Inventory/InventoryComponent.h"
#include "Net/UnrealNetwork.h"


APickUpItem::APickUpItem(): CountToAdd(0)
{
	PrimaryActorTick.bCanEverTick = false;
}

void APickUpItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APickUpItem, ItemToAdd)
	DOREPLIFETIME(APickUpItem, CountToAdd)
}


bool APickUpItem::StartInteract_Implementation(UInteractableComponent* Component, FInteractionAnimationInfo& InteractionInfo)
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
		Server_SuccessPickup();
	}
	
	return Success;
}
void APickUpItem::Server_SuccessPickup_Implementation()
{
	OnPickup();
	Destroy();
}

void APickUpItem::OnPickup_Implementation()
{
}
