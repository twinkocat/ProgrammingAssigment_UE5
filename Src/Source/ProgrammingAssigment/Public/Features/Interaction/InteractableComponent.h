// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class ABaseCharacter;

UENUM(BlueprintType)
enum EInteractionType : uint8
{
	None = 0,
	Pickup = 1,
};

USTRUCT(BlueprintType)
struct FInteractionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool SuccessInteract = false;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EInteractionType> InteractionType = EInteractionType::None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, FInteractionInfo, Info);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGRAMMINGASSIGMENT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UFUNCTION(BlueprintCallable)
	void StartInteract();

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;
	
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
