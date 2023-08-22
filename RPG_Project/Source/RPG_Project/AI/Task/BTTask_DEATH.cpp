// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DEATH.h"
#include "../AICharacter.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../Monster2.h"
#include "../../Global/GlobalEnums.h"
#include "../../Global/GlobalCoin.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../MainPlayer/MainPlayerCharacter.h"
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
		if (nullptr != Monster)
		{
			GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
			bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
			++Deathcnt1;
			GetGlobalGameInstance()->SetDeathMonster1(Deathcnt1);
			if (b)
			{
				Monster->SpawnCoinActor(Monster->GetActorLocation());
			}
			Monster->Destroy();		

			StateTime = 0.0f;
		}
		else if (nullptr != Monster2)
		{
			
			// ���⼭ ���� �÷��̾��� PlayerATT�� �����;��Ѵ�
			AMainPlayerCharacter* PlayerCh = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			hp2 = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("Monster2HP")); // hp �޾ƿ���
			Monster2->Sethp(hp2);
			
			hp2 = hp2-( PlayerCh->GetPlayerATT()); // att��ŭ ���� hp �޾ƿ´�
			

			GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster2HP"), hp2);
			Monster2->Sethp(hp2); // ���� set.
			
			if (hp2 > 0.0f) // ���� Hp�� 0���� ũ�ٸ�
			{
				int a = 0;
				StateTime = 0.0f;
				SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
				return;
			}

			else if (hp2 <= 0.0f) // Hp�� 0���� �۴ٸ�
			{
				int a = 0;
				hp2 = 0.0f;
				GetBlackboardComponent(OwnerComp)->SetValueAsFloat(TEXT("Monster2HP"), hp2); // ���⿡ ���� �÷��̾��� ���ݷ� ��ŭ hp ����
				// ���Ͱ� death �Ҷ� ������ �������� bool �Լ��� true��
				GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("SpawnCoin"), true);
				// SpawnCoin�� GET ���ش�
				bool b = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("SpawnCoin"));
				if (b)
				{
					Monster2->SpawnCoinActor(Monster2->GetActorLocation());
				}
				++Deathcnt2;
				GetGlobalGameInstance()->SetDeathMonster2(Deathcnt2);
				Monster2->Destroy();
			}
			StateTime = 0.0f;
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