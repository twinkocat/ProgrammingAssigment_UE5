// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WindowWidget.h"

TOptional<FUIInputConfig> UWindowWidget::GetDesiredInputConfig() const
{
	switch ( InputConfig )
	{
		case EWidgetInputMode3L::GameAndMenu:
			return FUIInputConfig( ECommonInputMode::All, GameMouseCaptureMode , MouseLockMode, bHideMouseDuringCapture);
		case EWidgetInputMode3L::Game:
			return FUIInputConfig( ECommonInputMode::Game, GameMouseCaptureMode , MouseLockMode, bHideMouseDuringCapture);
		case EWidgetInputMode3L::Menu:
			return FUIInputConfig( ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, MouseLockMode , bHideMouseDuringCapture);
	default:
			return Super::GetDesiredInputConfig();
	}
}
