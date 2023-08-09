// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DEATH.h"
#include "../AICharacter.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../../Global/GlobalEnums.h"
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

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_DEATH::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(GetAIState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();
	StateTime += DeltaSeconds;
	if (Time <= StateTime)
	{
		AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr != Monster)
		{
			++Deathcnt;
			GetGlobalGameInstance()->SetDeathMonster1(Deathcnt);
			//if (Deathcnt == 2)
			//{
			//	int a = 0;
			//}
			Monster->Destroy();		
			
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
