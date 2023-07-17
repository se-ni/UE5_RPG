// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Global/GlobalEnums.h"
#include "MainPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UMainPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;

	TMap<EAniState, class UAnimMontage*> AllAnimations;

	UFUNCTION()
		void MontageEnd(UAnimMontage* Anim, bool _Inter);

	// 애님인스턴용 Tick과 BeginPlay

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaTime) override;
};
