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

	GlobalAnimInstance = Cast<UGlobalAnimInstance>(GetMesh()->GetAnimInstance());

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
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 700.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 3000.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);

	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABoss::BeginOverlap);

	GetBlackboardComponent()->SetValueAsBool(TEXT("SpawnCoin"), false);

	GetBlackboardComponent()->SetValueAsFloat(TEXT("Boss1HP"), 0.3f); // 블랙보드 BossHP SET

	GlobalAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ABoss::AnimNotifyBegin);
}

void ABoss::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void ABoss::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int a = 0;
}
void ABoss::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	int a = 0;
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	TSubclassOf<UObject> Fire = Inst->GetSubClass(TEXT("Fire"));
	//TArray<UActorComponent*> StaticMeshs = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("WeaponMesh"));

	TArray<UActorComponent*> FireEffects = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("FireEffect"));

	USceneComponent* FireCom = Cast<USceneComponent>(FireEffects[0]);
	FVector Pos = FireCom->GetComponentToWorld().GetLocation();
	if (nullptr != Fire)
	{

		{ // 이펙트 만들기
			AttackEffect = GetWorld()->SpawnActor<AActor>(Fire);
			FVector effectloc = FVector(20.f, 0.f, 0.f) + GetActorLocation();
			AttackEffect->SetActorLocation(Pos);
			// Actor->SetActorScale3D(FVector(0.2f,0.2f,0.2f));
			// GetWorld()->GetTimerManager().SetTimer(EffectDestroyTimerHandle, this, &ABoss::DestroyAttackEffect, 5.0f, false);
		}
	}
}

void ABoss::DestroyAttackEffect()
{
	if (AttackEffect)
	{
		AttackEffect->Destroy();
		AttackEffect = nullptr;
	}
}