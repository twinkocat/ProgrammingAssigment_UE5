// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "WindowWidget.generated.h"

UENUM(BlueprintType)
enum class EWidgetInputMode3L : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

/**
 * 
 */
UCLASS()
class PROGRAMMINGASSIGMENT_API UWindowWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual TOptional< FUIInputConfig > GetDesiredInputConfig( ) const override;

	UPROPERTY( EditDefaultsOnly, Category = Input )
	bool bHideMouseDuringCapture = false;
	
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY( EditDefaultsOnly, Category = Input )
	EWidgetInputMode3L InputConfig = EWidgetInputMode3L::Default;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY( EditDefaultsOnly, Category = Input )
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY( EditDefaultsOnly, Category = Input )
	EMouseLockMode MouseLockMode = EMouseLockMode::DoNotLock;
};
