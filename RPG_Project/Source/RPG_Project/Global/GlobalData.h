// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalData.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UGlobalData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FRandomStream MainRandom;
};
