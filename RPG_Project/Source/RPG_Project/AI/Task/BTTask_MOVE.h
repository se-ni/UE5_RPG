// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Global/GlobalCharacter.h"
#include "BTTask_MOVE.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UBTTask_MOVE : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
		UBTTask_MOVE();
		void OnGameplayTaskActivated(class UGameplayTask&) override;


		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

		void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);



	
};
