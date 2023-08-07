// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_BASE.h"
#include "../../Global/GlobalCharacter.h"
#include "GameplayTask.h"
#include "BTTask_IDLE.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UBTTask_IDLE : public UBTTask_BASE
{
	GENERATED_BODY()

public:
		UBTTask_IDLE();

		//void SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State);
		void OnGameplayTaskActivated(class UGameplayTask&) override;
		UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);
		class AGlobalCharacter* GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp);

		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

		void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
		EAniState GetAIState(UBehaviorTreeComponent& OwnerComp);

		float StateTime=0.0f;

	
};
