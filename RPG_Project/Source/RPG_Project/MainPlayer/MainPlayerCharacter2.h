// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerCharacter.h"
#include "MainPlayerCharacter2.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMainPlayerCharacter2 : public AMainPlayerCharacter
{
	GENERATED_BODY()
public:
	void SetWeapon2();
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
