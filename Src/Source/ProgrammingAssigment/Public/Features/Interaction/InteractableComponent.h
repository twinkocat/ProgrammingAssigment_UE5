// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


class ABaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGRAMMINGASSIGMENT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UFUNCTION(BlueprintCallable)
	bool StartInteract();

	UFUNCTION(BlueprintCallable)
	bool EndInteract();
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool TryEvaluateInteractable(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	void ProcessInteractionHit(const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColliderCheckRadius;

	UPROPERTY(Transient)
	AActor* CachedOwner;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* LookingObject;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* InteractingObject;
};
