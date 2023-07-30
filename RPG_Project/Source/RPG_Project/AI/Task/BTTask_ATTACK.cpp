// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ATTACK.h"
#include "../MyAIController.h"
#include "../../Global/GlobalEnums.h"

UBTTask_ATTACK::UBTTask_ATTACK()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_ATTACK::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_ATTACK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Attack);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_ATTACK::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	FVector TargetPos = TargetActor->GetActorLocation();

	FVector Dir = TargetPos - PawnPos;

	GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
	// GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

	// AttackRange 보다 멀다면
	float AttackRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));

	if (AttackRange < Dir.Size())
	{
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Idle)); // 원래 자리로
		return;
	}
}