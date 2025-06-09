// Fill out your copyright notice in the Description page of Project Settings.

#include "ProgrammingAssigment/Public/Controllers/MyPlayerController.h"
#include "ProgrammingAssigment/Public/Features/Interaction/InteractableComponent.h"
#include "ProgrammingAssigment/Public/Features/Interaction/IInteractableComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CachedOwner = GetCharacter();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	AddMappingContext();
	SetupPlayerEnhanceInput(InputComponent);
}

void AMyPlayerController::AddMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AMyPlayerController::SetupPlayerEnhanceInput(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	check(EnhancedInputComponent != nullptr);

	// Move
	EnhancedInputComponent->BindAction(InputMoveAction,	ETriggerEvent::Triggered, this, &AMyPlayerController::HandleInputMove);

	// Interact
	EnhancedInputComponent->BindAction(InputInteractAction,	ETriggerEvent::Started, this, &AMyPlayerController::HandleInteract);

	// Look
	EnhancedInputComponent->BindAction(InputLookAction,	ETriggerEvent::Triggered, this, &AMyPlayerController::HandleLook);

}

void AMyPlayerController::HandleInputMove(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw - 90.F, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	CachedOwner->AddMovementInput(ForwardDirection, MoveVector.Y);
	CachedOwner->AddMovementInput(RightDirection, MoveVector.X); 
}

void AMyPlayerController::HandleInteract()
{
	if (UInteractableComponent* InteractableComponent = IIInteractableComponent::Execute_GetInteractableComponent(CachedOwner))
	{
		InteractableComponent->StartInteract();
	}
}

void AMyPlayerController::HandleLook(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	
	CachedOwner->AddControllerYawInput(LookVector.X);
	CachedOwner->AddControllerPitchInput(LookVector.Y);
}
