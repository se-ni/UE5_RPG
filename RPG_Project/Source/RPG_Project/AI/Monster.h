// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "../AI/MonsterData.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMonster : public AAICharacter
{
	GENERATED_BODY()

	const struct FMonsterData* CurMonsterData;

	void BeginPlay() override;
};
