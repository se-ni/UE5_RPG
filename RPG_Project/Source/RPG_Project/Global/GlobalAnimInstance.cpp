// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalAnimInstance.h"
#include "GlobalCharacter.h"

void UGlobalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UGlobalAnimInstance::MontageEnd);

	// ���� ���� ���͸� ���⼭ �����ɴϴ�.
	// TPSĳ���Ϳ��� �� ������ �����.

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

	// Anim ����� ��Ÿ��
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
