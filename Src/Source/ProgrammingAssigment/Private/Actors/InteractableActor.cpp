// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"
#include "Components/WidgetComponent.h"
#include "Features/Interaction/InteractableComponent.h"


AInteractableActor::AInteractableActor(): InteractionType()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Interactable");
	WidgetComponent->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	WidgetComponent->SetHiddenInGame(true);
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
	SetWidgetActive(true, Component);
}

void AInteractableActor::StopLooking_Implementation(UInteractableComponent* Component)
{
	SetWidgetActive(false, Component);
}

void AInteractableActor::SetWidgetActive(const bool bIsActive, const UInteractableComponent* Component)
{
	
	if (const AController* Controller = Component->GetOwner()->GetInstigatorController())
	{
		if (Controller->IsLocalController())
		{
			WidgetComponent->SetHiddenInGame(!bIsActive);	
		}
	}
}
