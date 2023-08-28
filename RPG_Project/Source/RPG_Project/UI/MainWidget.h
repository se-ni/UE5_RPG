// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPlayerStatusUIOnOffSwitch()
	{
		StatusUIOnOff = StatusUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetMinimapUIOnOffSwitch()
	{
		MinimapUIOnOff = MinimapUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetMinimap2UIOnOffSwitch()
	{
		Minimap2UIOnOff = Minimap2UIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetMinimap3UIOnOffSwitch()
	{
		Minimap3UIOnOff = Minimap3UIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetPlayerDeathUIOnOffSwitch()
	{
		SetPlayerDeathUIOnOff = SetPlayerDeathUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetPlayer2DeathUIOnOffSwitch()
	{
		SetPlayer2DeathUIOnOff = SetPlayer2DeathUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

private:
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility StatusUIOnOff = ESlateVisibility::Visible;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility MinimapUIOnOff = ESlateVisibility::Hidden;
	
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Minimap2UIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Minimap3UIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility SetPlayerDeathUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility SetPlayer2DeathUIOnOff = ESlateVisibility::Hidden;
};
