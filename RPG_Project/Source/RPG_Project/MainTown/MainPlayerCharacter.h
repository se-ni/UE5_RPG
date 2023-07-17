// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Global/GlobalEnums.h"
#include "MainPlayerCharacter.generated.h"

UCLASS()
class RPG_PROJECT_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMainPlayerCharacter();


	void AttackAction();
	void JumpAction();
	void JumpAxis(float Rate);

	
	void MoveRight(float Val);
	void MoveLeft(float Val);
	void MoveForward(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;

	bool AxisJump = false;

	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadOnly)
		bool isAttack = false;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;

	//UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	//	class UAnimMontage* RunAnimation;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<EAniState, class UAnimMontage*> AllAnimations;

	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly)
		float HP=0.9f;
	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly)
		float MP=1.f;
	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly)
		double Exp=1000;

	//UFUNCTION()
	//	void MontageEnd(UAnimMontage* Anim, bool _Inter);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
