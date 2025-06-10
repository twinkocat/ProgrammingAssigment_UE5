// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Interaction/InteractableComponent.h"
#include "Features/Interaction/Interactable.h"


UInteractableComponent::UInteractableComponent(): TraceLength(0), ColliderCheckRadius(0), CachedOwner(nullptr),
                                                  LookingObject(nullptr),
                                                  InteractingObject(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1F;
}


void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedOwner = GetOwner();
}

void UInteractableComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FVector ViewLocation = CachedOwner->GetActorLocation();
	const FRotator ViewRotator = CachedOwner->GetActorRotation();

	const FVector TraceEnd = ViewLocation + ViewRotator.Vector() * TraceLength;

	FHitResult HitResult(ForceInit);

	const bool bHit = TryEvaluateInteractable(HitResult, ViewLocation, TraceEnd);

	ProcessInteractionHit(HitResult);
}

bool UInteractableComponent::TryEvaluateInteractable(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	const FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, CachedOwner);

#if WITH_EDITOR
	DrawDebugSphere(GetWorld(), TraceEnd, ColliderCheckRadius, 1, FColor::Red, false, 0.25f, 0, 1.f);
#endif

	return GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceEnd, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(ColliderCheckRadius), TraceParams);
}

void UInteractableComponent::ProcessInteractionHit(const FHitResult& HitResult)
{
	AActor* NewLookingObject = HitResult.GetActor() != nullptr && HitResult.GetActor()->Implements<UInteractable>()
		                           ? HitResult.GetActor()
		                           : nullptr;

	if (NewLookingObject != LookingObject)
	{
		if (InteractingObject)
		{
			EndInteract();
		}

		if (LookingObject != nullptr)
		{
			IInteractable::Execute_StopLooking(LookingObject, this);
			LookingObject = nullptr;
		}

		LookingObject = NewLookingObject;

		if (!LookingObject || !IInteractable::Execute_IsInteractable(LookingObject, this))
		{
			return;
		}

		if (LookingObject != nullptr)
		{
			IInteractable::Execute_StartLooking(LookingObject, this);
		}
	}
}

bool UInteractableComponent::StartInteract()
{
	if (LookingObject == nullptr || !IInteractable::Execute_IsInteractable(LookingObject, this))
	{
		return false;
	}

	InteractingObject = LookingObject;
	IInteractable::Execute_StartInteract(InteractingObject, this);
	return true;
}

bool UInteractableComponent::EndInteract()
{
	if (InteractingObject == nullptr)
	{
		return false;
	}

	IInteractable::Execute_EndInteract(InteractingObject, this);
	InteractingObject = nullptr;
	return true;
}
