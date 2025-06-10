// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractableComponent.generated.h"

class UInteractableComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class UIInteractableComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGRAMMINGASSIGMENT_API IIInteractableComponent
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Interaction" )
	UInteractableComponent* GetInteractableComponent() const;

	virtual UInteractableComponent* GetInteractableComponent_Implementation() const = 0;
};
