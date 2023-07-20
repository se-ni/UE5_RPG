// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../Global/GlobalGameInstance.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"

void AMonster::BeginPlay()
{
	// UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	CurMonsterData = Inst->GetMonsterData(DataName);

	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIAniState"), static_cast<uint8>(AIAniState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
}
