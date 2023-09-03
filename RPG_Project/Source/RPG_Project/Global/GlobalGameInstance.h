// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "../AI/MonsterData.h"
#include "GlobalGameInstance.generated.h"

/**
 * 게임 내에서 공통적으로(전역으로) 사용되는 변수들의 집합
 */
UCLASS()
class RPG_PROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UGlobalGameInstance();
	~UGlobalGameInstance();

	UStaticMesh* GetMesh(FName _Name);

	struct FMonsterData* GetMonsterData(FName _Name);

	TSubclassOf<UObject> GetSubClass(FName _Name);

	/*struct FMonsterData* GetMonsterData(FName _Name);*/

	UFUNCTION()
	int GetDeathMonster1()
	{
		return DeathMonster1;
	}
	UFUNCTION()
	void SetDeathMonster1(int _int)
	{
		DeathMonster1 = _int;
	}

	int GetDeathMonster2()
	{
		return DeathMonster2;
	}
	UFUNCTION()
		void SetDeathMonster2(int _int)
	{
		DeathMonster2 = _int;
	}
	UFUNCTION()
		int GetStage3DeathMonster1()
	{
		return Stage3DeathMonster1Cnt;
	}
	UFUNCTION()
		void SetStage3DeathMonster1(int _int)
	{
		Stage3DeathMonster1Cnt = _int;
	}

	int GetStage3DeathMonster2()
	{
		return Stage3DeathMonster2Cnt;
	}
	UFUNCTION()
		void SetStage3DeathMonster2(int _int)
	{
		Stage3DeathMonster2Cnt = _int;
	}


	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
	int Coincnt = 0;
private:
	UPROPERTY(Category = "Monster1", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int DeathMonster1 = 0;

	UPROPERTY(Category = "Monster1", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Monster1Cnt = 3;

	UPROPERTY(Category = "Monster2", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int DeathMonster2 = 0;

	UPROPERTY(Category = "Monster2", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Monster2Cnt = 2;

	UPROPERTY(Category = "Stage3", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Stage3Monster1Cnt = 2;

	UPROPERTY(Category = "Stage3", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Stage3Monster2Cnt = 2;

	UPROPERTY(Category = "Stage3", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Stage3DeathMonster1Cnt = 0;

	UPROPERTY(Category = "Stage3", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Stage3DeathMonster2Cnt = 0;

	UPROPERTY()
		UDataTable* MeshDatas;

	UPROPERTY()
		UDataTable* MonsterDatas;

	UPROPERTY()
		UDataTable* SubClassDatas;
};