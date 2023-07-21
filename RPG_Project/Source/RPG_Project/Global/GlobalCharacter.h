// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GlobalCharacter.generated.h"

UCLASS()
class RPG_PROJECT_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGlobalCharacter();
	int GetAniState()
	{
		return AniState;
	}

	TMap<int, class UAnimMontage*> GetAllAnimations()
	{
		return AllAnimations;
	}

	void PushAnimation(int _Index, class UAnimMontage* _Montage)
	{
		if (true == AllAnimations.Contains(_Index))
		{
			return;
		}

		AllAnimations.Add(_Index, _Montage);
	}
	template<typename EnumType>
	void PushAnimation(EnumType _AIAniState, class UAnimMontage* _Montage)
	{
		if (true == AllAnimations.Contains(static_cast<int>(_AIAniState)))
		{
			return;
		}
		AllAnimations.Add(static_cast<int>(_AIAniState), _Montage);
	}

	template<typename EnumType>
	void SetAniState(EnumType _AniState)
	{
		AniState = static_cast<int>(_AniState);
	}

	void SetAniState(int _AniState)
	{
		AniState = _AniState;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		/*EAniState AniState = EAniState::Idle;*/
		int AniState = 0;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		/*TMap<EAniState, class UAnimMontage*> AllAnimations;*/
		TMap<int, class UAnimMontage*> AllAnimations;

};
