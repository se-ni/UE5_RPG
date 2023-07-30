// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MonsterPatrolData.generated.h"

/**
 * 
 */
USTRUCT()
struct RPG_PROJECT_API FMonsterPatrolData : public FTableRowBase
{
	GENERATED_BODY()

	FMonsterPatrolData() {}
	~FMonsterPatrolData() {}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "PatrolData")
		AActor* PatrolPointData;

};
