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
	// �ൿƮ�� ������Ʈ�� �����ͼ� null�� vaild������ �ƴ϶��
	if (nullptr != BehaviorTreeComponent && true == BehaviorTreeComponent->IsValidLowLevel())
	{
		// ĳ���͸� �����´�
		AAICharacter* CharacterAI = Cast<AAICharacter>(_InPawn);
		// ���� �ൿƮ���� AI�� �ൿƮ���� �Ҵ����ְ�
		UBehaviorTree* BehaviorTree = CharacterAI->GetBehaviorTree();
		
		
		// �� �ൿƮ���� null�� �ƴϸ�
		// �����带 �ൿƮ���� ������ �ִ� ������� �ʱ�ȭ
		// �������� ������ SelfActor �Ҵ�
		// �ൿƮ�� ������Ʈ�� StartTree ���ش�.
		
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