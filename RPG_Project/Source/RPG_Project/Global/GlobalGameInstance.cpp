// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include "PlayerWeaponData.h"

UGlobalGameInstance::UGlobalGameInstance() 
{
	FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/Data/DT_PlayerWeaponData.DT_PlayerWeaponData'");
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

	if (DataTable.Succeeded())
	{
		MeshDatas = DataTable.Object;
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