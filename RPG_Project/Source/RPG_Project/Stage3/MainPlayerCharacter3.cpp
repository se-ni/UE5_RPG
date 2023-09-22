// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter3.h"
#include "../MainPlayer/MainPlayerCharacter.h"
#include "../UI/MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Global/GlobalGameInstance.h"
#include "../Global/Fire.h"


AMainPlayerCharacter3::AMainPlayerCharacter3()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayerCharacter3::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->SetStaticMesh(WeaponArrays[2]);
	SetPlayerATT(0.7f);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayerCharacter3::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainPlayerCharacter3::EndOverlap);

	isWeapon1 = false;
	isWeapon2 = false;
	isWeapon3 = true;
}

void AMainPlayerCharacter3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float HP2 = GetPlayerHP();
	if (HP2 <= 0.0f)
	{
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
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("ShopUI"), EKeys::Insert));

	}
	PlayerInputComponent->BindAction("Weapon1", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon1);
	PlayerInputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon2);
	PlayerInputComponent->BindAction("Weapon3", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon3);

	PlayerInputComponent->BindAction("MinimapUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter3::Minimap3OnOff);
	PlayerInputComponent->BindAction("PlayerStateUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter3::Player3StateOnOff);
}

void AMainPlayerCharacter3::Player3StateOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetUIMainWidget()->SetPlayer3StateUIOnOffSwitch();
}

void AMainPlayerCharacter3::Minimap3OnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetUIMainWidget()->SetMinimap3UIOnOffSwitch();
}
void AMainPlayerCharacter3::Player3DeathOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}

	HUD->GetUIMainWidget()->SetPlayerDeathUIOnOffSwitch();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}
}

void AMainPlayerCharacter3::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFire* fire = Cast<AFire>(OtherActor);
	if (fire)
	{
		isoverlap = true;
		if (isoverlap)
		{
			MainPlayerAniState = EAniState::Hit;
		}
		float playerhp = GetPlayerHP();
		playerhp -= 0.4; // 0.4만큼 감소시키고
		SetPlayerHP(playerhp);
	}
}

void AMainPlayerCharacter3::EndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	isoverlap = false;
	MainPlayerAniState = EAniState::Idle;
}