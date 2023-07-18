// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Global/GlobalEnums.h"
#include "../Global/GlobalGameInstance.h"
#include "../TesShopWidget.h"
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

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;

	//UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	//	class UAnimMontage* RunAnimation;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<EAniState, class UAnimMontage*> AllAnimations;

	//UFUNCTION()
	//	void MontageEnd(UAnimMontage* Anim, bool _Inter);

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TSubclassOf<UUserWidget> ShopWidgetClass;
	UTesShopWidget* ShopUIWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool AxisJump = false;
	bool isOverlap = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(Category = "WeaponValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UStaticMesh*> WeaponArrays; // WeaponMesh 컴포넌트에서 이용할 WeaponMesh(스태틱 매쉬) 배열

	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float HP = 0.9f;
	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float MP = 1.f;
	UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		double Exp = 1000;
};
