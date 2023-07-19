// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalAnimInstance.h"
#include "GlobalCharacter.h"

void UGlobalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UGlobalAnimInstance::MontageEnd);

	// 나를 가진 액터를 여기서 가져옵니다.
	// TPS캐릭터에게 다 세팅을 해줬다.

	AGlobalCharacter* Chracter = Cast<AGlobalCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations;
}

void UGlobalAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	AGlobalCharacter* Chracter = Cast<AGlobalCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->GetAniState();

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

void UGlobalAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
	TSubclassOf<UAnimInstance> Inst = UGlobalAnimInstance::StaticClass();

	AGlobalCharacter* Chracter = Cast<AGlobalCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// Anim 종료된 몽타주
	if (AllAnimations[6] == Anim)
	{
		AniState = 0;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[0], 1.0f);
	}

	if (AllAnimations[5] == Anim)
	{
		AniState = 0;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[0], 1.0f);
	}

}
