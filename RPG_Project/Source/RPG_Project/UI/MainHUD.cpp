// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	// �������Ʈ�� ���� ���� ���� Ŭ���� ã�ƿ���
	FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_MainWidget.WBP_MainWidget_C'"));
	TSubclassOf<UUserWidget> MainWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

	// ã�ƿͼ� ����Ʈ��  add
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget = Cast<UMainWidget>(Widget);
	MainWidget->AddToViewport();

	// ���� �������� ��
	{
		UUserWidget* PlayerStatus = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_MainPlayerState")));
	}

	{
		UUserWidget* Minimap = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_Minimap")));
	}

	{
		UUserWidget* PlayerDeath = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_PlayerDeath")));
	}

	{
		UUserWidget* Player2Death = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_Player2Death")));
	}

	{
		UUserWidget* PlayerStatusUI = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_PlayerStatus")));
	}

	{
		UUserWidget* OptionStatusUI = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("WBP_Option")));
	}
}
void AMainHUD::Tick(float _Delta)
{
	Super::Tick(_Delta);
}