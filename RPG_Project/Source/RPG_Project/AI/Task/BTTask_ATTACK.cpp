// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ATTACK.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../Monster2.h"
#include "../Monster3.h"
#include "../Boss.h"
#include "../../MainPlayer/MainPlayerCharacter.h"
#include "../../MainPlayer/MainPlayerCharacter2.h"
#include "../../Stage3/MainPlayerCharacter3.h"
#include "../../Global/GlobalEnums.h"
#include "../../Global/Fire.h"
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
	// UGamplayStatics�� �̿��ؼ� MainPlayerCharacter �������� ��
	AMainPlayerCharacter2* Player2 = Cast<AMainPlayerCharacter2>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr != Mons2)
	{
		if (Mons2->isoverlap2) // �÷��̾�� ����2�� overlap ������
		{
			if (Player2)
			{
				float playhp = Player2->GetPlayerHP(); // �÷��̾��� hp �����ͼ�
				playhp = playhp - 0.2; // 0.3��ŭ ���ҽ�Ű��
				Player2->SetPlayerHP(playhp); // hp�� set ���ش�
			}
			Mons2->isoverlap2 = false; // overlap bool ������ �ٽ� false��.
		}
	}

	AMonster3* Mons3 = Cast<AMonster3>(GetGlobalCharacter(OwnerComp));
	// UGamplayStatics�� �̿��ؼ� MainPlayerCharacter �������� ��
	AMainPlayerCharacter3* Player3 = Cast<AMainPlayerCharacter3>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr != Mons3)
	{
		if (Mons3->isoverlap3) // �÷��̾�� ����2�� overlap ������
		{		
			if (Player3)
			{
				float playhp = Player3->GetPlayerHP(); // �÷��̾��� hp �����ͼ�
				playhp = playhp - 0.3; // 0.3��ŭ ���ҽ�Ű��
				Player3->SetPlayerHP(playhp); // hp�� set ���ش�
			}
			Mons3->isoverlap3 = false; // overlap bool ������ �ٽ� false��.
		}
	}

	//ABoss* bossMons = Cast<ABoss>(GetGlobalCharacter(OwnerComp));
	//// �÷��̾ fire�� �¾Ҵ�. �� ������ �����ͼ� ���Ͱ� player hp�� ��� �������Ѵ�.
	//if (nullptr != bossMons)
	//{
	//	if (true == Player3->isfireattack)
	//	{
	//		float playhp = Player3->GetPlayerHP(); // �÷��̾��� hp �����ͼ�
	//		playhp = playhp - 0.4; // 0.3��ŭ ���ҽ�Ű��
	//		Player3->SetPlayerHP(playhp); // hp�� set ���ش�
	//	}
	//}

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