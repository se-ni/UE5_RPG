// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.h"


AMyAIController::AMyAIController()
{
	// CreateDefaultSubobject // c++ 코드로 구현함으로써 기본값으로 설정
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCompnentonent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));;
}

// 빙의 순간 
// 캐릭터만들어지고 이제부터 컨트롤러가 이캐릭터를 조작할것이다.

void AMyAIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComponent && true == BehaviorTreeComponent->IsValidLowLevel())
	{
		AAICharacter* AIPawn = Cast<AAICharacter>(_InPawn);

		UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();

		if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())"), __FUNCTION__, __LINE__);
			return;
		}

		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

		BlackboardComponent->SetValueAsObject(TEXT("SelfActor"), _InPawn);

		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}

