// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonster::AMonster()
{

}

void AMonster::BeginPlay()
{	
	// Super::BeginPlay();


	UGlobalGameInstance* GameInst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != GameInst) // �۷ι������ν��Ͻ��� ���ؼ�
								// �ִϽ�����Ʈ�� �ִϸ��̼��� �������ش�
	{
		CurMonsterData = GameInst->GetMonsterData(DataName); // ���� ���͵����Ϳ� ���� �־��ְ�

		SetAllAnimation(CurMonsterData->MapAnimation);
		SetAniState(EAniState::None);
	}
	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIAniState"), static_cast<uint8>(EAniState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 200.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 1000.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

}