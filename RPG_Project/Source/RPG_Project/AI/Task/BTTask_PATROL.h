// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Global/GlobalCharacter.h"
#include "BTTask_BASE.h"
#include "GameplayTask.h"
#include "BTTask_PATROL.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UBTTask_PATROL : public UBTTask_BASE
{
	GENERATED_BODY()

public:
		UBTTask_PATROL();
		void OnGameplayTaskActivated(class UGameplayTask&) override;

		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

		void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

		void FindTarget(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	void FindPoint1(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	void FindPoint2(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
