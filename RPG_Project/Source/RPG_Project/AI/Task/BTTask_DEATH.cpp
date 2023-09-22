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

		if (nullptr != Monster)  // Stage ����1
		{
			// ���⼭ ���� �÷��̾��� PlayerATT�� �����;��Ѵ�
			AMainPlayerCharacter* PlayerCh = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (nullptr != PlayerCh)
			{
				hp1 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster1HP")); // hp �޾ƿ���

				hp1 = hp1 - (PlayerCh->GetPlayerATT()); // att��ŭ ���� hp �޾ƿ´�

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster1HP"), hp1);

				if (hp1 > 0.0f) // ���� Hp�� 0���� ũ�ٸ�
				{
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (hp1 <= 0.0f) // Hp�� 0���� �۴ٸ�
				{
					hp1 = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster1HP"), hp1); // ���⿡ ���� �÷��̾��� ���ݷ� ��ŭ hp ����
					// ���Ͱ� death �Ҷ� ������ �������� bool �Լ��� true��
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					// SpawnCoin�� GET ���ش�
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
			// ���⼭ ���� �÷��̾��� PlayerATT�� �����;��Ѵ�
			AMainPlayerCharacter* PlayerCh = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (nullptr != PlayerCh)
			{
				hp2 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster2HP")); // hp �޾ƿ���

				hp2 = hp2 - (PlayerCh->GetPlayerATT()); // att��ŭ ���� hp �޾ƿ´�

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster2HP"), hp2);

				if (hp2 > 0.0f) // ���� Hp�� 0���� ũ�ٸ�
				{
					int a = 0;
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (hp2 <= 0.0f) // Hp�� 0���� �۴ٸ�
				{
					hp2 = 0.0f;
					StateTime = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster1HP"), hp2); // ���⿡ ���� �÷��̾��� ���ݷ� ��ŭ hp ����
					// ���Ͱ� death �Ҷ� ������ �������� bool �Լ��� true��
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					int randCount = UGlobalData::MainRandom.RandRange(1, 3);
					// Coin�� spawn �Ѵ�
					bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
					if (b) // �������� ������ ���
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
				hp3 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster3HP")); // hp �޾ƿ���

				hp3 = hp3 - (PlayerCh3->GetPlayerATT()); // att��ŭ ���� hp �޾ƿ´�

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster3HP"), hp3);

				if (hp3 > 0.0f) // ���� Hp�� 0���� ũ�ٸ�
				{
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (hp3 <= 0.0f) // Hp�� 0���� �۴ٸ�
				{
					hp3 = 0.0f;
					StateTime = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster3HP"), hp3); // ���⿡ ���� �÷��̾��� ���ݷ� ��ŭ hp ����
					// ���Ͱ� death �Ҷ� ������ �������� bool �Լ��� true��
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					int randCount = UGlobalData::MainRandom.RandRange(1, 3);
					
					bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
					if (b) // �������� ������ ���
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
				bosshp = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("BossMonsterHP")); // hp �޾ƿ���

				bosshp = bosshp - (PlayerCh3->GetPlayerATT()); // att��ŭ ���� hp �޾ƿ´�

				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("BossMonsterHP"), bosshp);

				if (bosshp > 0.0f) // ���� Hp�� 0���� ũ�ٸ�
				{
					StateTime = 0.0f;
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}

				else if (bosshp <= 0.0f) // Hp�� 0���� �۴ٸ�
				{
					bosshp = 0.0f;
					StateTime = 0.0f;
					GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("BossMonsterHP"), bosshp); // ���⿡ ���� �÷��̾��� ���ݷ� ��ŭ hp ����
					// ���Ͱ� death �Ҷ� ������ �������� bool �Լ��� true��
					GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
					// SpawnCoin�� GET ���ش�
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