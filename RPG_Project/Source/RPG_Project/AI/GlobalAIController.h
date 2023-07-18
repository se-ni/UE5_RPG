// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GlobalAIController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AGlobalAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AGlobalAIController();
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
		class UBlackboardComponent* BlackboardComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorTreeComp; 

	void OnPossess(APawn* _InPawn);
};
