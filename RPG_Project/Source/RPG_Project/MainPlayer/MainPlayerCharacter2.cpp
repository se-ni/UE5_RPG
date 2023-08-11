// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter2.h"

void AMainPlayerCharacter2::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->SetStaticMesh(WeaponArrays[1]);
	PlayerATT = 50;
}
void AMainPlayerCharacter2::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;
		PlayerInputComponent->BindAction("Weapon1", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon1);
		PlayerInputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon2);
	}
}
