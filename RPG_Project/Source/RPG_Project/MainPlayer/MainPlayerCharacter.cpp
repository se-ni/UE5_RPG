// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"
#include "../AI/Monster.h"
#include "../AI/MyAIController.h"
#include "../UI/MainHUD.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FClassFinder<UUserWidget> ShopWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Level/Stage1/Shop/WBP_ShopUI.WBP_ShopUI_C'"));
	//if (ShopWidgetAsset.Succeeded())
	//	ShopWidgetClass = ShopWidgetAsset.Class;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	// 컴포넌트는 언리얼의 CDO 때문에 무조건 생성자에서 만들어줘야한다
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponSocket")); // 생성한 무기 매쉬를 캐릭터 매쉬에 붙여준다

}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = 2; // Jump Max Count = 2

	MainPlayerAnimInstance = Cast<UMainPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	//GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AMainPlayerCharacter::MontageEnd);
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayerCharacter::BeginOverlap);

	UGlobalGameInstance* Inst = GetGameInstance<UGlobalGameInstance>();
	WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Weapon1")));
	WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Weapon2")));
	WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Weapon3")));


	WeaponMesh->SetStaticMesh(WeaponArrays[0]); // 첫번째 무기
	PlayerATT = 0.3f;

	//AMyAIController* AICon = Cast<AMyAIController>(GetController());
	//AMonster* Mons = Cast<AMonster>(AICon->GetOwner());
	//if (Mons)
	//{
	//	UPrimitiveComponent* CapsuleComp = Mons->GetCapsuleComponent();
	//	if (CapsuleComp)
	//	{
	//		CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AMonster::MonsterOverlap);
	//	}
	//}
}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (true == isOverlap)
	//{
	//	if (IsValid(ShopWidgetClass))
	//	{
	//		ShopUIWidget = Cast<UTesShopWidget>(CreateWidget(GetWorld(), ShopWidgetClass));

	//		if (IsValid(ShopUIWidget))
	//		{
	//			ShopUIWidget->AddToViewport();
	//		}
	//	}
	//}
	if (HP <= 0.0f)
	{
		int a = 0;
		// 여기서 playerdeathuionoff 호출
		AMainPlayerCharacter::PauseGame();
		AMainPlayerCharacter::PlayerDeathOnOff();
	}
}


void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		// 축 매핑은 여기서 하고
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerJumpAxis", EKeys::J, -1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("Weapon1"), EKeys::One));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("Weapon2"), EKeys::Two));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("Weapon3"), EKeys::Three));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerStatusUI"), EKeys::P));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("MinimapUI"), EKeys::M));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("InteractionKey"), EKeys::E));

	}

	// 키와 함수를 연결합니다.

	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AMainPlayerCharacter::MoveForward);

	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AMainPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AMainPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AMainPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AMainPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AMainPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("PlayerJumpAxis", this, &AMainPlayerCharacter::JumpAxis);


	// Weapon Keys
	PlayerInputComponent->BindAction("Weapon1", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon1);
	//PlayerInputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon2);
	//PlayerInputComponent->BindAction("Weapon3", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::SetWeapon3);

	PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::AttackAction);
	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::JumpAction);

	PlayerInputComponent->BindAction("PlayerStatusUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::PlayerStatusOnOff);
	PlayerInputComponent->BindAction("MinimapUI", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::MinimapOnOff);
}


void AMainPlayerCharacter::PlayerStatusOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetMainWidget()->SetPlayerStatusUIOnOffSwitch();
}

void AMainPlayerCharacter::MinimapOnOff()
{
	APlayerController* MainCon = Cast<APlayerController>(GetController());
	AMainHUD* HUD = MainCon->GetHUD<AMainHUD>();

	if (nullptr == HUD && false == HUD->IsValidLowLevel())
	{
		return;
	}
	HUD->GetMainWidget()->SetMinimapUIOnOffSwitch();
}
void AMainPlayerCharacter::PlayerDeathOnOff()
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


void AMainPlayerCharacter::SetWeapon1()
{
	WeaponMesh->SetStaticMesh(WeaponArrays[0]);
	PlayerATT = 0.3f;
}
void AMainPlayerCharacter::SetWeapon2()
{
	WeaponMesh->SetStaticMesh(WeaponArrays[1]);
	PlayerATT = 0.5f;
}
void AMainPlayerCharacter::SetWeapon3()
{
	WeaponMesh->SetStaticMesh(WeaponArrays[2]);
	PlayerATT = 0.7f;
}


void AMainPlayerCharacter::MoveRight(float Val)
{
	if (MainPlayerAniState == EAniState::Attack || MainPlayerAniState == EAniState::JumpStart)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			//UE_LOG(LogTemp, Log, TEXT("%S(%u) %f"), __FUNCTION__, __LINE__, Val);
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// 현재 내 회전을 가져와서 y축에 해당하는 축벡터를 얻어오는 것.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);

			MainPlayerAniState = Val > 0.f ? EAniState::LeftMove : EAniState::RightMove;
			//UE_LOG(LogTemp, Log, TEXT("%S(%u)  %d"), __FUNCTION__, __LINE__, MainPlayerAniState);
			return;
		}
	}
	else
	{
		if (MainPlayerAniState == EAniState::RightMove || MainPlayerAniState == EAniState::LeftMove)
		{
			MainPlayerAniState = EAniState::Idle;
		}
	}
}

void AMainPlayerCharacter::MoveForward(float Val)
{
	if (MainPlayerAniState == EAniState::Attack || MainPlayerAniState == EAniState::JumpStart)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			// 컨트롤러는 기본적으로
			// charcter 하나씩 붙어 있습니다.
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// 이건 방향일 뿐입니다.
			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
			// 탑뷰게임이면 다르게 나오게 되는데.
			// 지금은 E를 하고 있기 때문에 컨트롤러의 회전이나 액터의 회전이나 같다.
			// AddMovementInput(GetActorForwardVector(), Val);

			MainPlayerAniState = Val > 0.f ? EAniState::ForwardMove : EAniState::BackwardMove ;
			//UE_LOG(LogTemp, Log, TEXT("%S(%u) %d"), __FUNCTION__, __LINE__, MainPlayerAniState);
			return;
		}
	}
	else
	{
		if (MainPlayerAniState == EAniState::ForwardMove || MainPlayerAniState == EAniState::BackwardMove)
		{
			MainPlayerAniState = EAniState::Idle;
		}
	}

}


void AMainPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AMainPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}


void AMainPlayerCharacter::JumpAxis(float Rate)
{
	if (0.0f == Rate)
	{
		if (true == AxisJump)
		{
			StopJumping();
			AxisJump = false;
		}
		return;
	}
	AxisJump = true;
	Jump();
}

void AMainPlayerCharacter::JumpAction()
{
	//UE_LOG(LogTemp, Log, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, JumpCurrentCount);
	Jump();

	MainPlayerAniState = EAniState::JumpStart;
}

void AMainPlayerCharacter::AttackAction()
{
	MainPlayerAniState = EAniState::Attack;
}

void AMainPlayerCharacter::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}