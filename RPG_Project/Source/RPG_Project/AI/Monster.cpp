// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMonster::BeginPlay()
{	
	Super::BeginPlay();

	UGlobalGameInstance* GameInst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != GameInst) // 글로벌게임인스턴스를 통해서
								// 애니스테이트와 애니메이션을 세팅해준다
	{
		CurMonsterData = GameInst->GetMonsterData(DataName); // 현재 몬스터데이터에 내용 넣어주고
		
		for (TPair<EAniState, UAnimMontage*> Pair : CurMonsterData->MapAnimation)
		{
			PushAnimation(Pair.Key, Pair.Value);
		}
		SetAniState(EAniState::Idle);
	}
	

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIAniState"), static_cast<uint8>(EAniState::Idle));
}