// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UMainWidget* GetUIMainWidget()
	{
		return UIMainWidget;
	}

protected:
	void BeginPlay() override;
	void Tick(float _Delta) override;

private:
		UPROPERTY(Category = "PlayerValue", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
			UMainWidget* UIMainWidget = nullptr;
};
