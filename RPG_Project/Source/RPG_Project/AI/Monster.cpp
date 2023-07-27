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

	if (nullptr != GameInst) // �۷ι������ν��Ͻ��� ���ؼ�
								// �ִϽ�����Ʈ�� �ִϸ��̼��� �������ش�
	{
		CurMonsterData = GameInst->GetMonsterData(DataName); // ���� ���͵����Ϳ� ���� �־��ְ�
		
		for (TPair<EAniState, UAnimMontage*> Pair : CurMonsterData->MapAnimation)
		{
			PushAnimation(Pair.Key, Pair.Value);
		}
		SetAniState(EAniState::Idle);
	}
	

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIAniState"), static_cast<uint8>(EAniState::Idle));
}