// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "MonsterData.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMonster : public AAICharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FMonsterData* CurMonsterData; // 현재 몬스터에 대한 데이터를 가지고 있음
};
