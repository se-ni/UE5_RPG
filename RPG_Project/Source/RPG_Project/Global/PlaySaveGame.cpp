// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySaveGame.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UPlaySaveGame::DataSave(ACharacter* Player)
{
	PlayerPos = Player->GetActorLocation();
	PlayerRot = Player->GetController()->GetControlRotation();
	PlayerScale = Player->GetActorScale();
}

void UPlaySaveGame::DataLoad(ACharacter* Player)
{
	Player->SetActorLocation(PlayerPos);
	Player->GetController()->SetControlRotation(PlayerRot);
	Player->SetActorScale3D(PlayerScale);
}