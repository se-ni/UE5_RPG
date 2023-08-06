// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_BASE.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PATROL.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UBTTask_PATROL : public UBTTask_BASE
{
	GENERATED_BODY()

	UBTTask_PATROL();

public:
	bool bReturning = false;

protected:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);

	AActor* GetTargetSearch(UBehaviorTreeComponent& OwnerComp);
};
