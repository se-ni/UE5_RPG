// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	// 블루프린트로 만든 메인 위젯 클래스 찾아오기
	FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_MainWidget.WBP_MainWidget_C'"));
	TSubclassOf<UUserWidget> MainWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

	// 찾아와서 뷰포트에  add
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	UIMainWidget = Cast<UMainWidget>(Widget);
	UIMainWidget->AddToViewport();

}
void AMainHUD::Tick(float _Delta)
{
	Super::Tick(_Delta);
}