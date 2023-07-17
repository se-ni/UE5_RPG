// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = 2; // Jump Max Count = 2

	//GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AMainPlayerCharacter::MontageEnd);

}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//class UAnimMontage* Montage = AllAnimations[AniState];

	//if (nullptr == Montage)
	//{
	//	return;
	//}

	//if (false == GetMesh()->GetAnimInstance()->Montage_IsPlaying(Montage))
	//{
	//	GetMesh()->GetAnimInstance()->Montage_Play(Montage, 1.0f);
	//}

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

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerJumpAxis", EKeys::J, -1.f));


		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::RightMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));

	}

	// 키와 함수를 연결합니다.
	
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AMainPlayerCharacter::MoveForward);
	
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AMainPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AMainPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AMainPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AMainPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AMainPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("PlayerJumpAxis", this, &AMainPlayerCharacter::JumpAxis);

	PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::AttackAction);
	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::JumpAction);

}


//void AMainPlayerCharacter::MontageEnd(UAnimMontage* Anim, bool _Inter)
//{
//		if (AllAnimations[EAniState::Attack] == Anim)
//		{
//			AniState = EAniState::Idle;
//			GetMesh()->GetAnimInstance()->Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
//		}
//	
//		if (AllAnimations[EAniState::JumpStart] == Anim)
//		{
//			AniState = EAniState::Idle;
//			GetMesh()->GetAnimInstance()->Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
//		}
//}

void AMainPlayerCharacter::MoveRight(float Val)
{
	if (AniState == EAniState::Attack || AniState == EAniState::JumpStart)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			UE_LOG(LogTemp, Log, TEXT("%S(%u) %f"), __FUNCTION__, __LINE__, Val);
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// 현재 내 회전을 가져와서 y축에 해당하는 축벡터를 얻어오는 겁니다.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
		
			AniState = Val > 0.f ? EAniState::RightMove : EAniState::LeftMove;
			UE_LOG(LogTemp, Log, TEXT("%S(%u)  %d"), __FUNCTION__, __LINE__, AniState);
			return;
		}
	}
	else
	{
		if (AniState == EAniState::RightMove || AniState == EAniState::LeftMove)
		{
			AniState = EAniState::Idle;
		}
	}
}

void AMainPlayerCharacter::MoveForward(float Val)
{
	if (AniState == EAniState::Attack || AniState == EAniState::JumpStart)
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
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			// 탑뷰게임이면 다르게 나오게 되는데.
			// 지금은 E를 하고 있기 때문에 컨트롤러의 회전이나 액터의 회전이나 같아요.
			// AddMovementInput(GetActorForwardVector(), Val);

			AniState = Val > 0.f ? EAniState::ForwardMove : EAniState::BackwardMove;
			UE_LOG(LogTemp, Log, TEXT("%S(%u) %d"), __FUNCTION__, __LINE__, AniState);
			return;
		}
	}
	else
	{
		if (AniState == EAniState::ForwardMove || AniState == EAniState::BackwardMove)
		{
			AniState = EAniState::Idle;
		}
	}

	// 이런 느낌의 함수 즉 static함수를 의미한다.
	// AEGLOBAL::DebugPrint("AAAAAAA");
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
	UE_LOG(LogTemp, Log, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, JumpCurrentCount);
	Jump();

	AniState = EAniState::JumpStart;
}

void AMainPlayerCharacter::AttackAction()
{
	AniState = EAniState::Attack;
}

