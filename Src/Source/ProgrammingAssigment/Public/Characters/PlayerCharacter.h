// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "ProgrammingAssigment/Public/Features/Interaction/IInteractableComponent.h"
#include "PlayerCharacter.generated.h"

class UInteractableComponent;

UCLASS()
class PROGRAMMINGASSIGMENT_API APlayerCharacter : public ABaseCharacter, public IIInteractableComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UInteractableComponent* InteractableComponent;

	
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UInteractableComponent* GetInteractableComponent_Implementation() const override;
};
