// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "MonsterData.h"
#include "../Global/GlobalEnums.h"
#include "../Global/GlobalGameInstance.h"
#include "../AI/MonsterPatrolData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Global/GlobalCoin.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMonster : public AAICharacter
{
	GENERATED_BODY()

	const struct FMonsterData* CurMonsterData; // 현재 몬스터에 대한 데이터

	void BeginPlay() override;

	void Tick(float DeltaSecond) override;

protected:


public:
	AMonster();

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

	UGlobalGameInstance* GetGlobalGameInstance();

	UFUNCTION(BlueprintCallable)
	void SpawnCoinActor(FVector _Loc)
	{
		FTransform Trans;
		Trans.SetLocation(_Loc);
		AActor* SpawnedActor0 = GetWorld()->SpawnActor<AActor>(CoinActor, Trans);
	}

	UPROPERTY(Category = "monster1", EditAnywhere, BlueprintReadWrite)
		float hp; // UI에게 넘겨주기 위해서 존재
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
	bool isoverlap; // 플레이어와 몬스터가 오버랩 됐음을 판단하는 bool 변수 
private:

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName DataName = "Monster1";

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EAniState AIAniState = EAniState::Idle;
	UPROPERTY(Category = "Monster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool isDeath = false;

	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGlobalCoin> CoinActor;

};

