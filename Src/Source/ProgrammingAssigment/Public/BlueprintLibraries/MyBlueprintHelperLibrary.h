// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBlueprintHelperLibrary.generated.h"

class UMyGameInstance;
/**
 * 
 */
UCLASS()
class PROGRAMMINGASSIGMENT_API UMyBlueprintHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyBlueprintHelperLibrary", meta = (WorldContext = "Context"))
	static UMyGameInstance* GetMyGameInstance(const UObject* Context);
};
