// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Global/GlobalCharacter.h"
#include "GameplayTask.h"

#include "BTTask_BASE.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UBTTask_BASE : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
		void OnGameplayTaskActivated(class UGameplayTask&) override;
		void SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State);
		class AGlobalCharacter* GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp);
		class UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);

		float StateTime = 0.0f;
};
