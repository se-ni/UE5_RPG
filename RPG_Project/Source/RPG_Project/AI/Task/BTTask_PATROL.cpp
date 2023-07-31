// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PATROL.h"
#include "../MyAIController.h"
#include "../Monster.h"
#include "../../Global/GlobalEnums.h"
#include "Kismet/GameplayStatics.h"

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

	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Patrol);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_PATROL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FindTarget(OwnerComp, NodeMemory, DeltaSeconds);

	FindPoint1(OwnerComp, NodeMemory, DeltaSeconds);

	//FindPoint2(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_PATROL::FindPoint1(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FString PointTag = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("PointTag1"));
	TArray<AActor*> PointActor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *PointTag, PointActor);
	AGlobalCharacter* Pawn = GetGlobalCharacter(OwnerComp);

	AActor* ResultActor = nullptr;

	if (0 != PointActor.Num())
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < PointActor.Num(); i++)
		{
			// float Dis = (Pawn->GetActorLocation() - PointActor[i]->GetActorLocation()).Size();
			ResultActor = PointActor[i];
		}
		if (nullptr != ResultActor)
		{
			GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("Point1"), ResultActor);
		}
	}
	FVector PointPos1 = ResultActor->GetActorLocation();
	GetGlobalCharacter(OwnerComp)->SetActorLocation(PointPos1);
}
void UBTTask_PATROL::FindPoint2(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FString PointTag2 = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("PointTag2"));
	TArray<AActor*> PointActor2;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *PointTag2, PointActor2);
	AGlobalCharacter* Pawn = GetGlobalCharacter(OwnerComp);

	AActor* ResultActor = nullptr;

	if (0 != PointActor2.Num())
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < PointActor2.Num(); i++)
		{
			// float Dis = (Pawn->GetActorLocation() - PointActor[i]->GetActorLocation()).Size();
			ResultActor = PointActor2[i];
		}
		if (nullptr != ResultActor)
		{
			GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("Point2"), ResultActor);
		}
	}
	FVector PointPos2 = ResultActor->GetActorLocation();
	GetGlobalCharacter(OwnerComp)->SetActorLocation(PointPos2);
}

void UBTTask_PATROL::FindTarget(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
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

			// SearchRange 안에 있다면
			float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));
			float Dis = (Pawn->GetActorLocation() - ResultActor->GetActorLocation()).Size();

			if (SearchRange > Dis)
			{
				SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
				return;
			}
		}
	}
}