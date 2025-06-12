// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibraries/MyBlueprintHelperLibrary.h"
#include "MyGameInstance.h"

UMyGameInstance* UMyBlueprintHelperLibrary::GetMyGameInstance(const UObject* Context)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	return World->GetGameInstance<UMyGameInstance>(); 
}
