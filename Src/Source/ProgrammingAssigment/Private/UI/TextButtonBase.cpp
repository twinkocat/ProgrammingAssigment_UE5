// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TextButtonBase.h"
#include "CommonTextBlock.h"


void UTextButtonBase::SetButtonText_Implementation(const FText& Text)
{
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

void UTextButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (TextBlock)
	{
		TextBlock->SetStyle(GetCurrentTextStyleClass());
	}
}