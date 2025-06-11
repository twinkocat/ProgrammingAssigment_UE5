// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"


AInteractableActor::AInteractableActor(): InteractionType()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AInteractableActor::IsInteractable_Implementation(UInteractableComponent* Component) const
{
	return true;
}

bool AInteractableActor::StartInteract_Implementation(UInteractableComponent* Component, FInteractionInfo& InteractionInfo)
{
	return true;
}

void AInteractableActor::StartLooking_Implementation(UInteractableComponent* Component)
{
}

void AInteractableActor::StopLooking_Implementation(UInteractableComponent* Component)
{
}
