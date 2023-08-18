// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GlobalEnums.h"
#include "GlobalAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UGlobalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		int AniState = 0;

	TMap<int, class UAnimMontage*> AllAnimations;

	UFUNCTION()
		void MontageEnd(UAnimMontage* Anim, bool _Inter);


	// �ִ��ν��Ͽ� Tick�� BeginPlay

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaTime) override;

};
