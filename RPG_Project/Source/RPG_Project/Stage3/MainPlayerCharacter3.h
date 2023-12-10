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
public:
	AMainPlayerCharacter3();

	bool isoverlap = false;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

protected:
	void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	void Player3StateOnOff();
	void Minimap3OnOff();
	void Player3DeathOnOff();
	void Status3OnOff();
};
