// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.generated.h"


USTRUCT(BlueprintType)
struct RPG_PROJECT_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

		FMonsterData() {}
	~FMonsterData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ATT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UBehaviorTree* AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TMap<EAniState, class UAnimMontage*> MapAnimation;
};
