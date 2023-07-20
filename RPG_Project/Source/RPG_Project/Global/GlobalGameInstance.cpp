// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include "PlayerWeaponData.h"
#include "UObject/ConstructorHelpers.h"

UGlobalGameInstance::UGlobalGameInstance() 
{
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_PlayerWeaponData.DT_PlayerWeaponData'");
		static ConstructorHelpers::FObjectFinder<UDataTable> MeshDataTable(*DataPath);

		if (true == MeshDataTable.Succeeded())
		{
			MeshDatas = MeshDataTable.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable>MonsterDataTable(TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_MonsterData.DT_MonsterData_C'"));
		if (true == MonsterDataTable.Succeeded())
		{
			MonsterDatas = MonsterDataTable.Object;
		}
	}
}

UGlobalGameInstance::~UGlobalGameInstance() 
{

}

UStaticMesh* UGlobalGameInstance::GetMesh(FName _Name)
{
	if (nullptr == MeshDatas)
	{
		return nullptr;
	}
	
	FPlayerWeaponData* FindTable = MeshDatas->FindRow<FPlayerWeaponData>(_Name, _Name.ToString());
	
	if (nullptr == FindTable)
	{
		return nullptr;
	}
	
	return FindTable->Mesh;
}

struct FMonsterData* UGlobalGameInstance::GetMonsterData(FName _Name)
{
	if (nullptr == MonsterDatas)
	{
		return nullptr;
	}

	FMonsterData* FindTable = MonsterDatas->FindRow<FMonsterData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}