// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APlayerCharacter;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROGRAMMINGASSIGMENT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	virtual void AddMappingContext();

	virtual void SetupPlayerEnhanceInput(UInputComponent* PlayerInputComponent);

	void HandleInputMove(const FInputActionValue& Value);
	void HandleInteract();
	void HandleLook(const FInputActionValue& Value);
	
	UPROPERTY(BlueprintReadOnly)
	ACharacter* CachedOwner;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Enhanced Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputInteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputLookAction;
};
