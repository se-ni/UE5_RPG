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
		if (Mons->isoverlap) // 플레이어와 몬스터가 overlap 됐을때
		{
			// UGamplayStatics를 이용해서 MainPlayerCharacter 가져오는 법
			AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (Player)
			{
				float playhp = Player->GetPlayerHP(); // 플레이어의 hp 가져와서
				playhp = playhp - 0.1; // 0.1만큼 감소시키고
				Player->SetPlayerHP(playhp); // hp로 set 해준다
			}
			Mons->isoverlap = false; // overlap bool 변수는 다시 false로.
		}
	}

	AMonster2* Mons2 = Cast<AMonster2>(GetGlobalCharacter(OwnerComp));
	// UGamplayStatics를 이용해서 MainPlayerCharacter 가져오는 법
	AMainPlayerCharacter2* Player2 = Cast<AMainPlayerCharacter2>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr != Mons2)
	{
		if (Mons2->isoverlap2) // 플레이어와 몬스터2가 overlap 됐을때
		{
			if (Player2)
			{
				float playhp = Player2->GetPlayerHP(); // 플레이어의 hp 가져와서
				playhp = playhp - 0.2; // 0.3만큼 감소시키고
				Player2->SetPlayerHP(playhp); // hp로 set 해준다
			}
			Mons2->isoverlap2 = false; // overlap bool 변수는 다시 false로.
		}
	}

	AMonster3* Mons3 = Cast<AMonster3>(GetGlobalCharacter(OwnerComp));
	// UGamplayStatics를 이용해서 MainPlayerCharacter 가져오는 법
	AMainPlayerCharacter3* Player3 = Cast<AMainPlayerCharacter3>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr != Mons3)
	{
		if (Mons3->isoverlap3) // 플레이어와 몬스터2가 overlap 됐을때
		{		
			if (Player3)
			{
				float playhp = Player3->GetPlayerHP(); // 플레이어의 hp 가져와서
				playhp = playhp - 0.3; // 0.3만큼 감소시키고
				Player3->SetPlayerHP(playhp); // hp로 set 해준다
			}
			Mons3->isoverlap3 = false; // overlap bool 변수는 다시 false로.
		}
	}

	//ABoss* bossMons = Cast<ABoss>(GetGlobalCharacter(OwnerComp));
	//// 플레이어가 fire에 맞았다. 그 변수를 가져와서 몬스터가 player hp를 깎게 만들어야한다.
	//if (nullptr != bossMons)
	//{
	//	if (true == Player3->isfireattack)
	//	{
	//		float playhp = Player3->GetPlayerHP(); // 플레이어의 hp 가져와서
	//		playhp = playhp - 0.4; // 0.3만큼 감소시키고
	//		Player3->SetPlayerHP(playhp); // hp로 set 해준다
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