// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalData.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"
#include "../UI/MainHUD.h"
#include "Blueprint/UserWidget.h"

FRandomStream UGlobalData::MainRandom;

void UGlobalData::UIMainWidgetOnOff(APlayerController* PlayerController, ESlateVisibility _Value)
{
    if (nullptr == PlayerController)
    {
        return;
    }

    AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD());

    if (nullptr == HUD)
    {
        return;
    }

    HUD->GetUIMainWidget()->SetVisibility(_Value);
}