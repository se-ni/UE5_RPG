// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ATTACK.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../Monster2.h"
#include "../../MainPlayer/MainPlayerCharacter.h"
#include "../../Global/GlobalEnums.h"
#include "Kismet/GameplayStatics.h"

UBTTask_ATTACK::UBTTask_ATTACK()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_ATTACK::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_ATTACK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Attack);
	AMonster* Mons = Cast<AMonster>(GetGlobalCharacter(OwnerComp));
	
	if (nullptr != Mons)
	{
		if (Mons->isoverlap) // �÷��̾�� ���Ͱ� overlap ������
		{
			// UGamplayStatics�� �̿��ؼ� MainPlayerCharacter �������� ��
			AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (Player)
			{
				float playhp = Player->GetPlayerHP(); // �÷��̾��� hp �����ͼ�
				playhp = playhp - 0.1; // 0.1��ŭ ���ҽ�Ű��
				Player->SetPlayerHP(playhp); // hp�� set ���ش�
			}
			Mons->isoverlap = false; // overlap bool ������ �ٽ� false��.
		}
	}

	AMonster2* Mons2 = Cast<AMonster2>(GetGlobalCharacter(OwnerComp));
	if (nullptr != Mons2)
	{
		if (Mons2->isoverlap2) // �÷��̾�� ����2�� overlap ������
		{
			// UGamplayStatics�� �̿��ؼ� MainPlayerCharacter �������� ��
			AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (Player)
			{
				float playhp = Player->GetPlayerHP(); // �÷��̾��� hp �����ͼ�
				playhp = playhp - 0.3; // 0.1��ŭ ���ҽ�Ű��
				Player->SetPlayerHP(playhp); // hp�� set ���ش�
			}
			Mons2->isoverlap2 = false; // overlap bool ������ �ٽ� false��.
		}
	}


	return EBTNodeResult::Type::InProgress;
}

void UBTTask_ATTACK::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(GetAIState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();

	StateTime += DeltaSeconds;
	if (Time <= StateTime)
	{
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
		StateTime = 0.0f;
	}
}

EAniState UBTTask_ATTACK::GetAIState(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return EAniState::None;
	}

	uint8 Enum = BlackBoard->GetValueAsEnum(TEXT("AIAniState"));

	return static_cast<EAniState>(Enum);
}