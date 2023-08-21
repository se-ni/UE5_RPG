// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter2.h"
#include "../UI/MainHUD.h"

void AMainPlayerCharacter2::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->SetStaticMesh(WeaponArrays[1]);
	SetPlayerATT(0.5f);
}
void AMainPlayerCharacter2::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;
		// UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("MinimapUI"), EKeys::M));

	}
		PlayerInputComponent->BindAction("Weapon1", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon1);
		PlayerInputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon2);
		
		PlayerInputComponent->BindAction("MinimapUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter2::Minimap2OnOff);
		
}

void AMainPlayerCharacter2::Minimap2OnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetMainWidget()->SetMinimap2UIOnOffSwitch();
}
