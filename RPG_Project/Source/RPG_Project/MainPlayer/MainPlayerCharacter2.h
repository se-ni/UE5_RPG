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
	AMainPlayerCharacter2();

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
	
	void Player2StateOnOff();
	void Minimap2OnOff();
	void Player2DeathOnOff();
	void Status2OnOff();

private:

};
