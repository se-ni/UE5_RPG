// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PATROL.h"
#include "../../Global/GlobalData.h"
#include "../PatrolPositions.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_PATROL::UBTTask_PATROL()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/*GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Patrol);*/


	int PatrolCount = UGlobalData::MainRandom.RandRange(3, 5);

	UPatrolPositions* PP = NewObject<UPatrolPositions>();
	GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("PatrolPositions"), PP);


	PP->CurrentIndex = 0;
	// TArray<FVector> Positions;

	FVector OriginPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("OriginPos"));
	float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));

	for (size_t i = 0; i < PatrolCount; i++)
	{
		FVector RandomDir;
		RandomDir.X = UGlobalData::MainRandom.FRandRange(-100.0f, 100.0f);
		RandomDir.Y = UGlobalData::MainRandom.FRandRange(-100.0f, 100.0f);
		RandomDir.Normalize();
		RandomDir *= UGlobalData::MainRandom.FRandRange(SearchRange * 1.2f, SearchRange);
		RandomDir += OriginPos;
		PP->Positions.Add(RandomDir);
	}

	PP->Positions.Add(OriginPos); // 내 원래 위치를 마지막에 add

	// OriginPos 를 포함하여 여러 포지션을 만들어서 넣어줬다
	// 여기에 넣었으므로 블랙보드 컴포넌트가 이 메모리를 지켜줄것이다를 생각하고 있다.

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_PATROL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);
	GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Idle);

	UObject* PPObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("PatrolPositions"));

	if (nullptr == PPObject)
	{
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Idle));
		return;
	}

	UPatrolPositions* PP = Cast<UPatrolPositions>(PPObject);

	TArray<FVector>& Positions = PP->Positions;
	int CurrentIndex = PP->CurrentIndex;

	if (CurrentIndex == Positions.Num())
	{
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::Idle));
		return;
	}

	FVector TargetPos = Positions[CurrentIndex];
	FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();


	AActor* ResultActor = GetTargetSearch(OwnerComp);

	if (nullptr != ResultActor)
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		SetStateChange(OwnerComp, static_cast<uint8>(EAniState::ForwardMove));
		return;
	}

	{
		// Patrol Point를 향해 회전하는 함수

		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
		Dir.Normalize();
	
		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;


		if (bReturning == false)
		{
			if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
			{
				FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 100.0f * DelataSeconds });
				GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
			}
			else
			{
				FRotator Rot = Dir.Rotation();
				GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);

				bReturning = true;
			}

		}
	}

	{
		// 앞으로 이동하는 함수

		FVector Dir = TargetPos - ThisPos;
		//Dir.Normalize();

		if (bReturning == true)
		{
			GetGlobalCharacter(OwnerComp)->SetAniState(EAniState::Patrol);

			GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);

			if (10.0f >= Dir.Size())
			{
				++PP->CurrentIndex;
				bReturning = false;
				return;
			}
		}
	}
}


AActor* UBTTask_PATROL::GetTargetSearch(UBehaviorTreeComponent& OwnerComp)
{
	FString TargetTag = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

	AGlobalCharacter* Pawn = GetGlobalCharacter(OwnerComp);

	float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));


	AActor* ResultActor = nullptr;

	if (0 != TargetActors.Num())
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Dis = (Pawn->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRange <= Dis)
			{
				continue;
			}

			if (Range > Dis)
			{
				Range = Dis;
				ResultActor = TargetActors[i];
			}
		}
	}

	return ResultActor;
}
