// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RETURN.h"
#include "../AICharacter.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../../Global/GlobalEnums.h"

UBTTask_RETURN::UBTTask_RETURN()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


void UBTTask_RETURN::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_RETURN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Return);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_RETURN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	OriginAIPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("OriginPos"));

	FVector TargetPos = OriginAIPos;
	FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
	// 혹시라도 z축이 있을 가능성을 없애는게 보통입니다.
	TargetPos.Z = 0.0f;
	ThisPos.Z = 0.0f;

	FVector Dir = TargetPos - ThisPos;
	Dir.Normalize();
	{
		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 15.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 20.0f * DeltaSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else
		{
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}
	}

	FVector NowPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	Dir = TargetPos - NowPos;

	GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);

	if (Dir.X < 0.5f)
	{
		bReturning = true;
	}

	//UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(UBTTask_AIBase::GetAiState(OwnerComp));
	//float Time = Montage->CalculateSequenceLength();

	//if (Time <= GetStateTime(OwnerComp))
	//{
	//	SetStateChange(OwnerComp, AIState::IDLE);
	//	// GetGlobalCharacter(OwnerComp)->SetAniState(AIState::IDLE);
	//	return;
	//}

	if (bReturning)
	{

		GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Idle);
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Idle));
		bReturning = false;
	}
}

