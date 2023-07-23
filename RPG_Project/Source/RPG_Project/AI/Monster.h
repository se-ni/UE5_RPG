// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "MonsterData.h"
#include "../Global/GlobalEnums.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMonster : public AAICharacter
{
	GENERATED_BODY()

	const struct FMonsterData* CurMonsterData; // ���� ���Ϳ� ���� ������

	void BeginPlay() override;
private:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName DataName = "Monster1";

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EAniState AiAniState = EAniState::Idle;
};

