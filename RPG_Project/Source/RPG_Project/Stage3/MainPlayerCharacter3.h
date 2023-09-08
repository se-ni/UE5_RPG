// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MainPlayer/MainPlayerCharacter.h"
#include "MainPlayerCharacter3.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMainPlayerCharacter3 : public AMainPlayerCharacter
{
	GENERATED_BODY()

protected:
	void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	void Minimap3OnOff();
	void Player3DeathOnOff();
};
