// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "PlayerWeaponData.generated.h"

/**
 * 
 */
USTRUCT()
struct RPG_PROJECT_API FPlayerWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	FPlayerWeaponData() {}
	~FPlayerWeaponData() {}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MeshData")
		UStaticMesh* Mesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MeshData")
		int WeaponATT;
	
};
