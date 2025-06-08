﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgrammingAssigment/Public/Characters/PlayerCharacter.h"
#include "ProgrammingAssigment/Public/Features/Interaction/InteractableComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UInteractableComponent* APlayerCharacter::GetInteractableComponent_Implementation() const
{
	return InteractableComponent;
}

