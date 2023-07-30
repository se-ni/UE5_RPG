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
	FString PathToPatrolPoint = TEXT("/Game/Global/Monster/PatrolPoint.PatrolPoint_C'");

	// ��Ʈ������Ʈ �������Ʈ Ŭ���� �ε�
	UClass* PatrolPointBPClass = LoadClass<AActor>(nullptr, *PathToPatrolPoint);
	if (PatrolPointBPClass)
	{
		FVector SpawnLocation = FVector(0, 0, 0); // ���ϴ� ��ġ ������ ��ü���ּ���.
		FRotator SpawnRotation = FRotator(0, 0, 0); // ���ϴ� ȸ�� ������ ��ü���ּ���.

		// ��Ʈ������Ʈ ����
		PatrolPointReference = GetWorld()->SpawnActor<AActor>(PatrolPointBPClass, SpawnLocation, SpawnRotation);
	}
	else
	{
		// �ε� ���� �� ���� �޽��� ���
		UE_LOG(LogTemp, Error, TEXT("Failed to load PatrolPoint blueprint class."));
	}
}

void AMonster::BeginPlay()
{	
	// Super::BeginPlay();
	OriginPos = GetActorLocation();

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
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 100.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 500.0f);

}