// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MOVE.h"
#include "../MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Global/GlobalCharacter.h"
#include "../Monster.h"
#include "GameFramework/Actor.h"
#include "Math/Quat.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../../Global/GlobalEnums.h"

UBTTask_MOVE::UBTTask_MOVE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;

}

void UBTTask_MOVE::OnGameplayTaskActivated(UGameplayTask& _Task)
{
	Super::OnGameplayTaskActivated(_Task);
}

EBTNodeResult::Type UBTTask_MOVE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);
	
	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::ForwardMove);


	return EBTNodeResult::Type::InProgress;
}

void UBTTask_MOVE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (nullptr == TargetActor)
	{
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Return));
		return;
	}

	{
		FVector TargetPos = TargetActor->GetActorLocation();
		FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		// Ȥ�ö� z���� ���� ���ɼ��� ���ִ°� �����Դϴ�.
		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
		Dir.Normalize();

		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 12.0f * DeltaSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else {
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}
	}



	{
		FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		FVector TargetPos = TargetActor->GetActorLocation();

		FVector Dir = TargetPos - PawnPos;

		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		// GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

		// SearchRange �ȿ� �ִٸ�
		float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));

		if (SearchRange < Dir.Size())
		{
			SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Idle)); // ���� �ڸ���
			return;
		}

		float AttackRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));


		// ����� �����ߴ�.
		if (AttackRange >= Dir.Size())
		{
			SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Attack));
			return;
		}

	}
}

//void UBTTask_MOVE::SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State)
//{
//	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
//
//	if (nullptr == BlackBoard)
//	{
//		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
//		return;
//	}
//
//	BlackBoard->SetValueAsEnum(TEXT("AIAniState"), _State);
//
//	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
//}