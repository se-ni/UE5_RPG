// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

protected:
	void OnPossess(APawn* _InPawn) override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
		class UBlackboardComponent* BlackboardComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorTreeComp; 

	
};
