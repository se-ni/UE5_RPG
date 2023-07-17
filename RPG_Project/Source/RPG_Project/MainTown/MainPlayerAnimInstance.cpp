// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerAnimInstance.h"
#include "MainPlayerCharacter.h"

void UMainPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UMainPlayerAnimInstance::MontageEnd);

	// 나를 가진 액터를 여기서 가져옵니다.
	// TPS캐릭터에게 다 세팅을 해줬다.

	AMainPlayerCharacter* Chracter = Cast<AMainPlayerCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations;
}

void UMainPlayerAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	AMainPlayerCharacter* Chracter = Cast<AMainPlayerCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->AniState;

	class UAnimMontage* Montage = AllAnimations[AniState];

	if (nullptr == Montage)
	{
		return;
	}

	if (false == Montage_IsPlaying(Montage))
	{
		Montage_Play(Montage, 1.0f);
	}
}

void UMainPlayerAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
	TSubclassOf<UAnimInstance> Inst = UMainPlayerAnimInstance::StaticClass();

	AMainPlayerCharacter* Chracter = Cast<AMainPlayerCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// Anim 종료된 몽타주
	if (AllAnimations[EAniState::Attack] == Anim)
	{
		AniState = EAniState::Idle;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}

	if (AllAnimations[EAniState::JumpStart] == Anim)
	{
		AniState = EAniState::Idle;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}

}
