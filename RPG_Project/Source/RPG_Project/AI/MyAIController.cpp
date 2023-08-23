// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MainPlayer/MainPlayerCharacter.h"
#include "../Global/GlobalCharacter.h"
#include "AICharacter.h"

AMyAIController::AMyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AMyAIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);
	// 행동트리 컴포넌트를 가져와서 null과 vaild레벨이 아니라면
	if (nullptr != BehaviorTreeComponent && true == BehaviorTreeComponent->IsValidLowLevel())
	{
		// 캐릭터를 가져온다
		AAICharacter* CharacterAI = Cast<AAICharacter>(_InPawn);
		// 새로 행동트리를 AI의 행동트리로 할당해주고
		UBehaviorTree* BehaviorTree = CharacterAI->GetBehaviorTree();
		
		
		// 이 행동트리가 null이 아니면
		// 블랙보드를 행동트리가 가지고 있는 블랙보드로 초기화
		// 블랙보드의 변수인 SelfActor 할당
		// 행동트리 컴포넌트를 StartTree 해준다.
		
		if (nullptr == BehaviorTree && false == BehaviorTree->IsValidLowLevel())
		{
			return;
		}
			BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
			BlackboardComponent->SetValueAsObject(TEXT("SelfActor"), _InPawn);
			// BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), _InPawn);
		
			BehaviorTreeComponent->StartTree(*BehaviorTree);


	}

}