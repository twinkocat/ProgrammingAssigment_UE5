// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class UInteractableComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGRAMMINGASSIGMENT_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Interaction" )
	bool IsInteractable(UInteractableComponent* Component) const;

	UFUNCTION( BlueprintNativeEvent, Category = "Interaction" )
	bool StartInteract(UInteractableComponent* Component);

	UFUNCTION( BlueprintNativeEvent, Category = "Interaction" )
	void EndInteract(UInteractableComponent* Component);

	UFUNCTION( BlueprintNativeEvent, Category = "Interaction" )
	void StartLooking(UInteractableComponent* Component);

	UFUNCTION( BlueprintNativeEvent, Category = "Interaction" )
	void StopLooking(UInteractableComponent* Component);

	virtual bool IsInteractable_Implementation(UInteractableComponent* Component) const = 0;

	virtual bool StartInteract_Implementation(UInteractableComponent* Component) = 0;
	virtual void EndInteract_Implementation(UInteractableComponent* Component) = 0;

	virtual void StartLooking_Implementation(UInteractableComponent* Component) = 0;
	virtual void StopLooking_Implementation(UInteractableComponent* Component) = 0;
};
