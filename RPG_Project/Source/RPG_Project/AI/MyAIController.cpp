// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	// CreateDefaultSubobject // c++ �ڵ�� ���������ν� �⺻������ ����
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCompnent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));;
}

// ���� ���� 
// ĳ���͸�������� �������� ��Ʈ�ѷ��� ��ĳ���͸� �����Ұ��̴�.

void AMyAIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComp && true == BehaviorTreeComp->IsValidLowLevel())
	{
		BehaviorTreeComp;
		BlackboardComp;

	}
}

