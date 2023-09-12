// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Global/GlobalEnums.h"
#include "../Global/GlobalGameInstance.h"
#include "../TesShopWidget.h"
#include "../Global/GlobalCharacter.h"
#include "MainPlayerAnimInstance.h"
#include "../Global/PlayerWeaponData.h"
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

	void SetWeapon1();
	void SetWeapon2();
	void SetWeapon3();


	void MoveRight(float Val);
	void MoveLeft(float Val);
	void MoveForward(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void PlayerStateOnOff();
	void MinimapOnOff();
	void PlayerDeathOnOff();

	void StatusOnOff();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		EAniState MainPlayerAniState = EAniState::Idle;
	// 기존에 정의되어 있는 클래스의 멤버변수인 AniState를 물려받아, cpp 파일에서 함수를 구현함.

	//UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	//	class UAnimMontage* RunAnimation;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<EAniState, class UAnimMontage*> MainPlayerAllAnimations ;

	UFUNCTION()
	bool GetIsDeath()
	{
		return isDeath;
	}
	UFUNCTION()
	float GetPlayerATT()
	{
		return PlayerATT;
	}

	void SetPlayerATT(float _ATT)
	{
		PlayerATT = _ATT;
	}
	UFUNCTION()
	float GetPlayerHP()
	{
		return HP;
	}

	void SetPlayerHP(float _HP)
	{
		HP = _HP;
	}
	UFUNCTION()
	float GetPlayerMP()
	{
		return MP;
	}

	void SetPlayerMP(float _MP)
	{
		MP = _MP;
	}

	bool isWeapon1 = false;
	bool isWeapon2 = false;
	bool isWeapon3 = false;

	// 함수를 통해 애님 인스턴스를 가져옵니다.
	UFUNCTION(BlueprintPure, Category = "Animation")
		UMainPlayerAnimInstance* GetMainPlayerAnimInstance() const { return MainPlayerAnimInstance; }

	void PauseGame();

	// bool isweapon2 = false;

	//bool Getisweapon2()
	//{
	//	return isweapon2;
	//}

	//void Setisweapon2(bool _b)
	//{
	//	isweapon2 = _b;
	//}

	float destroyTime = 3.0f;
	AActor* AttackEffect;

	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 애님 인스턴스를 저장할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		UMainPlayerAnimInstance* MainPlayerAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;
	UPROPERTY(Category = "WeaponValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UStaticMesh*> WeaponArrays; // WeaponMesh 컴포넌트에서 이용할 WeaponMesh(스태틱 매쉬) 배열
	
	void DestroyAttackEffect();

private:
	FTimerHandle EffectDestroyTimerHandle; // 타이머 핸들변수
	bool AxisJump = false;
	bool isOverlap = false;


		bool isDeath = false; // 몬스터의 죽음 판별할 변수

	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		/*int PlayerATT = 10;*/
		float PlayerATT ; 
	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float HP = 1.f;
	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float MP = 1.f;

	/*UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		double Exp = 1000;*/

	// const struct FPlayerWeaponData* CurWeaponData;
	
	UFUNCTION()
		void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
