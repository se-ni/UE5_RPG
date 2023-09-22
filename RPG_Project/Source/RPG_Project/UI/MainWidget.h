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

	void SetPlayerStateUIOnOffSwitch()
	{
		PlayerStateOnOff = PlayerStateOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetPlayer2StateUIOnOffSwitch()
	{
		Player2StateOnOff = Player2StateOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetPlayer3StateUIOnOffSwitch()
	{
		Player3StateOnOff = Player3StateOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
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
		PlayerDeathUIOnOff = PlayerDeathUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetPlayer2DeathUIOnOffSwitch()
	{
		Player2DeathUIOnOff = Player2DeathUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetPlayer3DeathUIOnOffSwitch()
	{
		Player3DeathUIOnOff = Player3DeathUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}
	
	void SetStatusUIOnOffSwitch()
	{
		StatusUIOnOff = StatusUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetOptionUIOnOffSwitch()
	{
		OptionUIOnOff = OptionUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetInvenUIOnOffSwitch()
	{
		InvenUIOnOff = InvenUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetShopUIOnOffSwitch()
	{
		ShopUIOnOff = ShopUIOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

private:
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility PlayerStateOnOff = ESlateVisibility::Hidden; // State UI

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Player2StateOnOff = ESlateVisibility::Hidden; // State UI

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Player3StateOnOff = ESlateVisibility::Hidden; // State UI

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility MinimapUIOnOff = ESlateVisibility::Hidden;
	
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Minimap2UIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Minimap3UIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility PlayerDeathUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Player2DeathUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility Player3DeathUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility StatusUIOnOff = ESlateVisibility::Hidden; // Status UI

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility OptionUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility InvenUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility ShopUIOnOff = ESlateVisibility::Hidden;
};
