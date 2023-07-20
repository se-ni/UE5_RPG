// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyAIController.h"
UBlackboardComponent* AAICharacter::GetBlackboardComponent()
{
	if (nullptr == BlackboardComponent)
	{
		AMyAIController* MyAICon = GetController<AMyAIController>();

		if (nullptr == MyAICon)
		{
			return nullptr;
		}

		BlackboardComponent = MyAICon->GetBlackboardComponent();
	}

	return BlackboardComponent;
}