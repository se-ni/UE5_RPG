// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_BASE.h"
#include "BTTask_RETURN.h"
#include "../MyAIController.h"
#include "../../Global/GlobalEnums.h"

void UBTTask_BASE::OnGameplayTaskActivated(class UGameplayTask&)
{

}

void UBTTask_BASE::SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	BlackBoard->SetValueAsEnum(TEXT("AIAniState"), _State);

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
}
void UBTTask_BASE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool isDeath = GetBlackboardComponent(OwnerComp)->GetValueAsBool(TEXT("bIsDeath"));

	if (isDeath)
	{
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Death));
		return;
	}
}
AGlobalCharacter* UBTTask_BASE::GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp)
{
	AMyAIController* AiCon = OwnerComp.GetOwner<AMyAIController>(); // 컨트롤러를 가져오고
	if (nullptr == AiCon || false == AiCon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 상태
		return nullptr;
	}

	// 컨트롤러가 조작하는 Pawn은 GetPawn을 사용해서 가져온다.
	AGlobalCharacter* Character = AiCon->GetPawn<AGlobalCharacter>();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 상태
		return nullptr;
	}

	return Character;
}

UBlackboardComponent* UBTTask_BASE::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	AMyAIController* AiCon = OwnerComp.GetOwner<AMyAIController>();
	UBlackboardComponent* blackboard = AiCon->GetBlackboardComponent();
	
	return blackboard;
}

//float UBTTask_BASE::GetStateTime(UBehaviorTreeComponent& OwnerComp)
//{
//	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();
//
//	if (nullptr == BlockBoard)
//	{
//		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
//		return 0.0f;
//	}
//
//	StateTime = BlockBoard->GetValueAsFloat(TEXT("StateTime"));
//
//	return StateTime;
//}
