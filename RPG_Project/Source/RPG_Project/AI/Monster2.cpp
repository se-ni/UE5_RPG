// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster2.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "../MainPlayer/MainPlayerCharacter2.h"

AMonster2::AMonster2()
{
	//hp = 1.0f;
}

void AMonster2::BeginPlay()
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
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 100.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 700.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);

	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AMonster2::BeginOverlap);

	GetBlackboardComponent()->SetValueAsBool(TEXT("SpawnCoin"), false);

	GetBlackboardComponent()->SetValueAsFloat(TEXT("Monster2HP"), 1.0f); // 블랙보드 Monster2HP SET

}

void AMonster2::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

}

void AMonster2::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	{
		AMainPlayerCharacter2* Player2 = Cast<AMainPlayerCharacter2>(OtherActor);
		if (Player2)
		{

			// 플레이어의 애님 인스턴스 가져오기
			UMainPlayerAnimInstance* PlayerAnimInstance = Player2->GetMainPlayerAnimInstance();
			if (PlayerAnimInstance)
			{
				if (PlayerAnimInstance->GetCurrentAnimationState() == EAniState::Attack)
				{
					isoverlap2 = false; // 플레이어가 공격중일때는, hp 감소 x
					GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), true);
				}
				else
				{
					isoverlap2 = true;
					GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);
				}
			}
		}
	}
}

UGlobalGameInstance* AMonster2::GetGlobalGameInstance()
{
	UGlobalGameInstance* inst = Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != inst)
	{
		return inst;
	}
	return nullptr;
}

void AMonster2::Setbdeathfalse()
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);
}