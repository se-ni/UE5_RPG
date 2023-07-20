// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	// CreateDefaultSubobject // c++ 코드로 구현함으로써 기본값으로 설정
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCompnent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));;
}

// 빙의 순간 
// 캐릭터만들어지고 이제부터 컨트롤러가 이캐릭터를 조작할것이다.

void AMyAIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComp && true == BehaviorTreeComp->IsValidLowLevel())
	{
		BehaviorTreeComp;
		BlackboardComp;

	}
}

