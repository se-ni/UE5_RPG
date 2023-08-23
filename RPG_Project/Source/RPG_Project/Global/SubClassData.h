// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "SubClassData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RPG_PROJECT_API FSubClassData : public FTableRowBase
{
	GENERATED_BODY()
	
	FSubClassData() {}
	~FSubClassData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<UObject> Object;
};
