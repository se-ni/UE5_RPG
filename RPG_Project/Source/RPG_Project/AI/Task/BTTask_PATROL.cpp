// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PATROL.h"
#include "../MyAIController.h"
#include "../../Global/GlobalEnums.h"

UBTTask_PATROL::UBTTask_PATROL()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_PATROL::OnGameplayTaskActivated( UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_PATROL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
