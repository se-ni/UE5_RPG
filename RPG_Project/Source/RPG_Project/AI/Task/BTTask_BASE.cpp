// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_BASE.h"
#include "BTTask_RETURN.h"
#include "../MyAIController.h"
#include "../../Global/GlobalEnums.h"

void UBTTask_BASE::OnGameplayTaskActivated(class UGameplayTask&)
{

}

AGlobalCharacter* UBTTask_BASE::GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp)
{
	AMyAIController* AiCon = OwnerComp.GetOwner<AMyAIController>(); // ��Ʈ�ѷ��� ��������
	if (nullptr == AiCon || false == AiCon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// ���������� ���� ����
		return nullptr;
	}

	// ��Ʈ�ѷ��� �����ϴ� Pawn�� GetPawn�� ����ؼ� �����´�.
	AGlobalCharacter* Character = AiCon->GetPawn<AGlobalCharacter>();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// ���������� ���� ����
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

