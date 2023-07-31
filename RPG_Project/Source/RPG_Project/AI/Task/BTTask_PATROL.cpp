// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PATROL.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../../Global/GlobalEnums.h"

UBTTask_PATROL::UBTTask_PATROL()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_PATROL::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Patrol);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_PATROL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	//FVector PatrolPoint = Monster->GetPatrolPointLocation();
	//FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	//FVector Dir = PatrolPoint - ThisPos;

	//GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);


}
