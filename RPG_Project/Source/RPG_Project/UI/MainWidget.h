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

	void SetPlayerDeathUIOnOffSwitch()
	{
		SetPlayerDeathUIOnOff = Minimap2UIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

private:
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility StatusUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility MinimapUIOnOff = ESlateVisibility::Hidden;
	
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Minimap2UIOnOff = ESlateVisibility::Hidden;
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility SetPlayerDeathUIOnOff = ESlateVisibility::Hidden;
	
};
