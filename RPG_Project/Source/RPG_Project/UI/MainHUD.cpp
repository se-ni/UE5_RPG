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
	UIMainWidget = Cast<UMainWidget>(Widget);
	UIMainWidget->AddToViewport();

}
void AMainHUD::Tick(float _Delta)
{
	Super::Tick(_Delta);
}