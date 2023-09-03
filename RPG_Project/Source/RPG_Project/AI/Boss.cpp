// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "../MainPlayer/MainPlayerCharacter.h"
#include "../Global/Projectile.h"

ABoss::ABoss()
{

}

void ABoss::BeginPlay()
{	
	// Super::BeginPlay();


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
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 500.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 3000.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);

	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABoss::BeginOverlap);

	GetBlackboardComponent()->SetValueAsBool(TEXT("SpawnCoin"), false);

	GetBlackboardComponent()->SetValueAsFloat(TEXT("Boss1HP"), 0.3f); // 블랙보드 Boss2HP SET
}

void ABoss::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void ABoss::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(OtherActor);
		if (nullptr != Player)
		{
			
			// 플레이어의 애님 인스턴스 가져오기
			UMainPlayerAnimInstance* PlayerAnimInstance = Player->GetMainPlayerAnimInstance();
			if (PlayerAnimInstance)
			{
				if (PlayerAnimInstance->GetCurrentAnimationState() == EAniState::Attack)
				{
					isoverlap = false; // 플레이어가 공격중일때는, hp 감소 x
					GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), true);
				}
				else
				{
					isoverlap = true;
					GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);
				}
			}
		}
}