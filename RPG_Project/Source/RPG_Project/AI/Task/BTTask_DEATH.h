// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BASE.h"
#include "../../Global/GlobalCharacter.h"
#include "../../Global/GlobalGameInstance.h"
#include "GameplayTask.h"
#include "BTTask_DEATH.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UBTTask_DEATH : public UBTTask_BASE
{
	GENERATED_BODY()

public:
		UBTTask_DEATH();
		void OnGameplayTaskActivated(UGameplayTask& _Task) override;

		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

		void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
		EAniState GetAIState(UBehaviorTreeComponent& OwnerComp);
		UGlobalGameInstance* GetGlobalGameInstance();

private:
	float StateTime = 0.0f;
	UPROPERTY(Category = "Monster1", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Deathcnt1 = 0;

	UPROPERTY(Category = "Monster2", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Deathcnt2 = 0;

	UPROPERTY(Category = "Monster3", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Deathcnt3 = 0;

	UPROPERTY(Category = "BossMonster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Deathcnt4 = 0;

	bool SpawnBPCoin;
	/*FVector ActorLoc;*/

	float hp1;
	float hp2;
	float hp3;
	float bosshp;

	//UFUNCTION()
	//	void MainPlayer1Attack(UBehaviorTreeComponent& OwnerComp);
	//UFUNCTION()
	//	void MainPlayer2Attack(UBehaviorTreeComponent& OwnerComp);
	
};
