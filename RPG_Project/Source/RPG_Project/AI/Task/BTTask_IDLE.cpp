// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IDLE.h"
#include "../MyAIController.h"
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
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return BlockBoard;
}
void UBTTask_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

}

AGlobalCharacter* UBTTask_IDLE::GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp)
{
	AMyAIController* AICon = OwnerComp.GetOwner<AMyAIController>();
	if (nullptr == AICon || false == AICon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// ���������� ���� ������ 
		return nullptr;
	}

	// ��Ʈ�ѷ����� ���� �����ϴ� Pawn�� GetPawn�� ����Ѵ�.
	AGlobalCharacter* Character = AICon->GetPawn<AGlobalCharacter>();
	Character->AniState;
	Character->AllAnimations;
	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// ���������� ���� ����
		return nullptr;
	}

	return Character;

}



