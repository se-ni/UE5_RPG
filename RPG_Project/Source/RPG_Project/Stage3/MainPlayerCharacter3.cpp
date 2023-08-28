// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter3.h"
#include "../MainPlayer/MainPlayerCharacter.h"
#include "../UI/MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Global/GlobalGameInstance.h"

void AMainPlayerCharacter3::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->SetStaticMesh(WeaponArrays[2]);
	SetPlayerATT(0.7f);
	isWeapon2 = false;
	AMainPlayerCharacter* Main = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// Main->Setisweapon2(true);
	int a = 0;
}

void AMainPlayerCharacter3::Tick(float DeltaTime)
{
	float HP2 = GetPlayerHP();
	if (HP2 <= 0.0f)
	{
		int a = 0;
		// 여기서 player2deathuionoff 호출
		AMainPlayerCharacter::PauseGame();
		AMainPlayerCharacter3::Player3DeathOnOff();
	}
}
void AMainPlayerCharacter3::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
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
	PlayerInputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon3);

	PlayerInputComponent->BindAction("MinimapUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter3::Minimap3OnOff);

}

void AMainPlayerCharacter3::Minimap3OnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetMainWidget()->SetMinimap3UIOnOffSwitch();
}
void AMainPlayerCharacter3::Player3DeathOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetMainWidget()->SetPlayerDeathUIOnOffSwitch();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}
}