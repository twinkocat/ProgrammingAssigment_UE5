// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Features/Interaction/IInteractableComponent.h"
#include "Features/Inventory/IInventoryComponent.h"
#include "PlayerCharacter.generated.h"

class UInteractableComponent;
class UInventoryComponent;

UCLASS()
class PROGRAMMINGASSIGMENT_API APlayerCharacter : public ABaseCharacter, public IIInteractableComponent,
                                                  public IIInventoryComponent
{
	GENERATED_BODY()
	
protected:
	APlayerCharacter();
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UInteractableComponent* GetInteractableComponent_Implementation() const override;
	virtual UInventoryComponent* GetInventoryComponent_Implementation() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UInventoryComponent* InventoryComponent;
};
