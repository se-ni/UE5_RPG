// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlaySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UPlaySaveGame : public USaveGame
{
	GENERATED_BODY()


public:
	UPROPERTY(Category = "Save Data", EditAnywhere, BlueprintReadWrite)
		FVector PlayerPos;

	UPROPERTY(Category = "Save Data", EditAnywhere, BlueprintReadWrite)
		FRotator PlayerRot;

	UPROPERTY(Category = "Save Data", EditAnywhere, BlueprintReadWrite)
		FVector PlayerScale;

	UFUNCTION(BlueprintCallable, Category = "PlaySaveGame")
		void DataSave(ACharacter* _Character);

	UFUNCTION(BlueprintCallable, Category = "PlaySaveGame")
		void DataLoad(ACharacter* _Character);
};
