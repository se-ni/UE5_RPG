// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "MonsterData.h"
#include "../Global/GlobalEnums.h"
#include "../Global/GlobalGameInstance.h"
#include "../Global/GlobalAnimInstance.h"
#include "../AI/MonsterPatrolData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Global/GlobalCoin.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API ABoss : public AAICharacter
{
	GENERATED_BODY()

	const struct FMonsterData* CurMonsterData; // ���� ���Ϳ� ���� ������

	void BeginPlay() override;

	void Tick(float DeltaSecond) override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:


public:
	ABoss();

	// Declare the collision component
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComp;

	//FVector GetPatrolPointLocation()
	//{
	//	return PatrolPointReference->GetActorLocation();
	//}
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintCallable)
	void SpawnCoinActor(FVector _Loc)
	{
		FTransform Trans;
		Trans.SetLocation(_Loc);
		AActor* SpawnedActor0 = GetWorld()->SpawnActor<AActor>(CoinActor, Trans);
	}

	UPROPERTY(Category = "monster1", EditAnywhere, BlueprintReadWrite)
		float hp; // UI���� �Ѱ��ֱ� ���ؼ� ����
	UFUNCTION()
		float Gethp()
	{
		return hp;
	}
	UFUNCTION()
		void Sethp(float _hp)
	{
		hp = _hp;
	}
	bool isoverlap; // �÷��̾�� ���Ͱ� ������ ������ �Ǵ��ϴ� bool ���� 

private:

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName DataName = "Boss";

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EAniState AIAniState = EAniState::Idle;
	UPROPERTY(Category = "BossMonster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool isDeath = false;

	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGlobalCoin> CoinActor;
	
	UFUNCTION()
	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
	FTimerHandle EffectDestroyTimerHandle; // Ÿ�̸� �ڵ麯��

	void DestroyAttackEffect();

	AActor* AttackEffect = nullptr;
};

