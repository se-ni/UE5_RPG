// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonster::AMonster()
{
	FString PathToPatrolPoint = TEXT("/Game/Global/Monster/PatrolPoint.PatrolPoint_C'");

	// 패트롤포인트 블루프린트 클래스 로드
	UClass* PatrolPointBPClass = LoadClass<AActor>(nullptr, *PathToPatrolPoint);
	if (PatrolPointBPClass)
	{
		FVector SpawnLocation = FVector(0, 0, 0); // 원하는 위치 값으로 대체해주세요.
		FRotator SpawnRotation = FRotator(0, 0, 0); // 원하는 회전 값으로 대체해주세요.

		// 패트롤포인트 생성
		PatrolPointReference = GetWorld()->SpawnActor<AActor>(PatrolPointBPClass, SpawnLocation, SpawnRotation);
	}
	else
	{
		// 로드 실패 시 에러 메시지 출력
		UE_LOG(LogTemp, Error, TEXT("Failed to load PatrolPoint blueprint class."));
	}
}

void AMonster::BeginPlay()
{	
	// Super::BeginPlay();
	OriginPos = GetActorLocation();

	UGlobalGameInstance* GameInst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != GameInst) // 글로벌게임인스턴스를 통해서
								// 애니스테이트와 애니메이션을 세팅해준다
	{
		CurMonsterData = GameInst->GetMonsterData(DataName); // 현재 몬스터데이터에 내용 넣어주고

		SetAllAnimation(CurMonsterData->MapAnimation);
		SetAniState(EAniState::None);
	}
	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIAniState"), static_cast<uint8>(EAniState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 100.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 500.0f);

}