// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DEATH.h"
#include "../AICharacter.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../Monster2.h"
#include "../Monster3.h"
#include "../Boss.h"
#include "../../Global/GlobalEnums.h"
#include "../../Global/GlobalCoin.h"
#include "../../Global/GlobalData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../MainPlayer/MainPlayerCharacter.h"
#include "../../Stage3/MainPlayerCharacter3.h"
#include "Kismet/GameplayStatics.h"

UBTTask_DEATH::UBTTask_DEATH()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


void UBTTask_DEATH::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_DEATH::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Death);

	//monster2hp = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster2HP"));

	return EBTNodeResult::Type::InProgress;
}


void UBTTask_DEATH::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	/*ActorLoc = GetGlobalCharacter(OwnerComp)->GetActorLocation();*/
	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(GetAIState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();
	StateTime += DeltaSeconds;
	if (Time <= StateTime)
	{
		AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
		AMonster2* Monster2 = Cast<AMonster2>(OwnerComp.GetAIOwner()->GetPawn());

		AMonster3* Monster3 = Cast<AMonster3>(OwnerComp.GetAIOwner()->GetPawn());
		ABoss* BossMons = Cast<ABoss>(OwnerComp.GetAIOwner()->GetPawn());

		if (nullptr != Monster)  // Stage 몬스터1
		{
			// 여기서 이제 플레이어의 PlayerATT를 가져와야한다
			AMainPlayerCharacter* PlayerCh = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (nullptr != PlayerCh)
			{
				hp1 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster1HP")); // hp 받아오기

				hp1 = hp1 - (PlayerCh->GetPlayerATT()); // att만큼 빼준 hp 받아온다

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster1HP"), hp1);

				if (hp1 > 0.0f) // 아직 Hp가 0보다 크다면
				{
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (hp1 <= 0.0f) // Hp가 0보다 작다면
				{
					hp1 = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster1HP"), hp1); // 무기에 따른 플레이어의 공격력 만큼 hp 감소
					// 몬스터가 death 할때 코인을 스폰해줄 bool 함수를 true로
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					// SpawnCoin을 GET 해준다
					bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
					if (b)
					{
						Monster->SpawnCoinActor(Monster->GetActorLocation());
					}
					++Deathcnt1;
					GetGlobalGameInstance()->SetDeathMonster1(Deathcnt1);
					Monster->Destroy();
				}
				StateTime = 0.0f;
			}
		}

		else if (nullptr != Monster2)
		{
			// 여기서 이제 플레이어의 PlayerATT를 가져와야한다
			AMainPlayerCharacter* PlayerCh = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (nullptr != PlayerCh)
			{
				hp2 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster2HP")); // hp 받아오기

				hp2 = hp2 - (PlayerCh->GetPlayerATT()); // att만큼 빼준 hp 받아온다

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster2HP"), hp2);

				if (hp2 > 0.0f) // 아직 Hp가 0보다 크다면
				{
					int a = 0;
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (hp2 <= 0.0f) // Hp가 0보다 작다면
				{
					hp2 = 0.0f;
					StateTime = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster1HP"), hp2); // 무기에 따른 플레이어의 공격력 만큼 hp 감소
					// 몬스터가 death 할때 코인을 스폰해줄 bool 함수를 true로
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					int randCount = UGlobalData::MainRandom.RandRange(1, 3);
					// Coin을 spawn 한다
					bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
					if (b) // 랜덤으로 아이템 드롭
					{
						if (randCount == 1)
						{
							Monster2->SpawnCherryActor(Monster2->GetActorLocation());
						}
						if (randCount == 2)
						{
							Monster2->SpawnCoinActor(Monster2->GetActorLocation());
						}
					}
					++Deathcnt2;
					GetGlobalGameInstance()->SetDeathMonster2(Deathcnt2);
					Monster2->Destroy();
				}	
			}
		}

		else if (nullptr != Monster3)
		{
			AMainPlayerCharacter3* PlayerCh3 = Cast<AMainPlayerCharacter3>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (nullptr != PlayerCh3)
			{
				int a = 0;
				hp3 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster3HP")); // hp 받아오기

				hp3 = hp3 - (PlayerCh3->GetPlayerATT()); // att만큼 빼준 hp 받아온다

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster3HP"), hp3);

				if (hp3 > 0.0f) // 아직 Hp가 0보다 크다면
				{
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (hp3 <= 0.0f) // Hp가 0보다 작다면
				{
					hp3 = 0.0f;
					StateTime = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster3HP"), hp3); // 무기에 따른 플레이어의 공격력 만큼 hp 감소
					// 몬스터가 death 할때 코인을 스폰해줄 bool 함수를 true로
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					int randCount = UGlobalData::MainRandom.RandRange(1, 3);
					
					bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
					if (b) // 랜덤으로 아이템 드롭
					{
						if (randCount == 1)
						{
							Monster3->SpawnCherryActor(Monster3->GetActorLocation());
						}
						if (randCount == 2)
						{
							Monster3->SpawnPotActor(Monster3->GetActorLocation());
						}
					}
					++Deathcnt3;
					GetGlobalGameInstance()->SetDeathMonster3(Deathcnt3);
					Monster3->Destroy();
				}
			}
		}
		else if (nullptr != BossMons)
		{
			AMainPlayerCharacter3* PlayerCh3 = Cast<AMainPlayerCharacter3>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (nullptr != PlayerCh3)
			{
				bosshp = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("BossMonsterHP")); // hp 받아오기

				bosshp = bosshp - (PlayerCh3->GetPlayerATT()); // att만큼 빼준 hp 받아온다

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("BossMonsterHP"), bosshp);

				if (bosshp > 0.0f) // 아직 Hp가 0보다 크다면
				{
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (bosshp <= 0.0f) // Hp가 0보다 작다면
				{
					bosshp = 0.0f;
					StateTime = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("BossMonsterHP"), bosshp); // 무기에 따른 플레이어의 공격력 만큼 hp 감소
					// 몬스터가 death 할때 코인을 스폰해줄 bool 함수를 true로
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					// SpawnCoin을 GET 해준다
					bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
					if (b)
					{
						BossMons->SpawnCoinActor(BossMons->GetActorLocation());
					}
					++Deathcnt4;
					GetGlobalGameInstance()->SetDeathMonster4(Deathcnt4);
					BossMons->Destroy();
				}
			}
		}	
	}
}


EAniState UBTTask_DEATH::GetAIState(UBehaviorTreeComponent& OwnerComp)
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

UGlobalGameInstance* UBTTask_DEATH::GetGlobalGameInstance()
{
	UGlobalGameInstance* inst = Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != inst)
	{
		int a = 0;
		return inst;
	}
	return nullptr;
}