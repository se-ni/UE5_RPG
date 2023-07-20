// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.h"


AMyAIController::AMyAIController()
{
	// CreateDefaultSubobject // c++ �ڵ�� ���������ν� �⺻������ ����
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCompnentonent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));;
}

// ���� ���� 
// ĳ���͸�������� �������� ��Ʈ�ѷ��� ��ĳ���͸� �����Ұ��̴�.

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

