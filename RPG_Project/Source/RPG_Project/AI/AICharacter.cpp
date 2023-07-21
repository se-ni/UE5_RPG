// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyAIController.h"

UBlackboardComponent* AAICharacter::GetBlackboardComponent()
{
	if (nullptr == BlackboardComponent)
	{
		AMyAIController* AICon = GetController<AMyAIController>();
		
		if (nullptr == AICon)
		{
			return nullptr;
		}
		BlackboardComponent = AICon->GetBlackboardComponent();
	}
	return BlackboardComponent;

}