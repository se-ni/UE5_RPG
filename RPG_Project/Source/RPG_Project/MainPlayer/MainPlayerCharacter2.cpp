// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter2.h"
#include "MainPlayerCharacter.h"
#include "../UI/MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Global/GlobalGameInstance.h"
#include "../AI/Monster2.h"


AMainPlayerCharacter2::AMainPlayerCharacter2()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayerCharacter2::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->SetStaticMesh(WeaponArrays[1]);
	SetPlayerATT(0.5f);
	AMainPlayerCharacter* Main = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// Main->Setisweapon2(true);
	isWeapon1 = false;
	isWeapon2 = true;
	isWeapon3 = false;
}

void AMainPlayerCharacter2::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMonster2* Mon2 = Cast<AMonster2>(OtherActor);
	if (Mon2)
	{
		MainPlayerAniState = EAniState::Hit;
	}
}

void AMainPlayerCharacter2::EndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	MainPlayerAniState = EAniState::Idle;
}

void AMainPlayerCharacter2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float HP2 = GetPlayerHP();
	if (HP2 - 0.2f <= 0.0f)
	{
		// 여기서 player2deathuionoff 호출
		//AMainPlayerCharacter::PauseGame();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		AMainPlayerCharacter2::Player2DeathOnOff();
	}
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
		PlayerInputComponent->BindAction("PlayerStateUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter2::Player2StateOnOff);
		PlayerInputComponent->BindAction("StatusUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter2::Status2OnOff);
}

void AMainPlayerCharacter2::Status2OnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetUIMainWidget()->SetStatus2UIOnOffSwitch();
}

void AMainPlayerCharacter2::Player2StateOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetUIMainWidget()->SetPlayer2StateUIOnOffSwitch();
}

void AMainPlayerCharacter2::Minimap2OnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetUIMainWidget()->SetMinimap2UIOnOffSwitch();
}
void AMainPlayerCharacter2::Player2DeathOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetUIMainWidget()->SetPlayer2DeathUIOnOffSwitch();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}
}