// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IDLE.h"
#include "../MyAIController.h"
#include "../../Global/GlobalCharacter.h"
#include "../../Global/GlobalEnums.h"

UBTTask_IDLE::UBTTask_IDLE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_IDLE::OnGameplayTaskActivated(class UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_IDLE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Idle);
	return EBTNodeResult::Type::InProgress;
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
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlackBoard)"), __FUNCTION__, __LINE__);
		return EAniState::None;
	}

	uint8 Enum = BlackBoard->GetValueAsEnum(TEXT("AIAniState"));

	return static_cast<EAniState>(Enum);
}

void UBTTask_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(GetAIState(OwnerComp));
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
	Character->AniState;
	Character->AllAnimations;
	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 뭔가
		return nullptr;
	}
	
	return Character;
	
}



