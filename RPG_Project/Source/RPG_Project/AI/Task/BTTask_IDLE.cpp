// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IDLE.h"
#include "../MyAIController.h"
#include "../../Global/GlobalCharacter.h"
#include "../../Global/GlobalEnums.h"
#include "Kismet/GameplayStatics.h"

UBTTask_IDLE::UBTTask_IDLE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;

	
}

void UBTTask_IDLE::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

UBlackboardComponent* UBTTask_IDLE::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlackBoard)"), __FUNCTION__, __LINE__);
		return nullptr;
	}
	return BlackBoard;
}

EAniState UBTTask_IDLE::GetAIState(UBehaviorTreeComponent& OwnerComp)
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

EBTNodeResult::Type UBTTask_IDLE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Idle);

	return EBTNodeResult::Type::InProgress;
}



void UBTTask_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	//SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Idle));
	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(GetAIState(OwnerComp));

	StateTime += DeltaSeconds;

	if (StateTime >= 5.0f)
	{
		int a = 0;
		UE_LOG(LogTemp, Log, TEXT("%S(%u) %f"), __FUNCTION__, __LINE__, StateTime);
		// SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));

		FString TargetTag = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("TargetTag"));
		TArray<AActor*> TargetActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

		AGlobalCharacter* Pawn = GetGlobalCharacter(OwnerComp);

		if (0 != TargetActors.Num())
		{
			AActor* ResultActor = nullptr;
			float Range = TNumericLimits<float>::Max();

			for (size_t i = 0; i < TargetActors.Num(); i++)
			{
				float Dis = (Pawn->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();
				ResultActor = TargetActors[i];

			}
				if (nullptr != ResultActor)
				{
					GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
					SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
					return;
				}
		}

	}

}

void UBTTask_IDLE::SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	BlackBoard->SetValueAsEnum(TEXT("AIAniState"), _State);
	StateTime = 0.0f;

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
}

AGlobalCharacter* UBTTask_IDLE::GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp)
{
	AMyAIController* AICon = OwnerComp.GetOwner<AMyAIController>();
	if (nullptr == AICon || false == AICon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 뭔가가 
		return nullptr;
	}

	// 컨트롤러에게 내가 조작하는 Pawn은 GetPawn을 사용한다.
	AGlobalCharacter* Character = AICon->GetPawn<AGlobalCharacter>();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 뭔가
		return nullptr;
	}

	return Character;

}
