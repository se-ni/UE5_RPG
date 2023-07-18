// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AGlobalAIController::AGlobalAIController()
{
	// CreateDefaultSubobject // c++ 코드로 구현함으로써 기본값으로 설정
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCompnent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));;
}

void AGlobalAIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComp && true == BehaviorTreeComp->IsValidLowLevel())
	{
		// BehaviorTreeComp->StartTree();
	}
}

