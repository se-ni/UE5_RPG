// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "../AI/Monster2.h"
#include "../AI/Monster3.h"
#include "../AI/Boss.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp = GetSphereComponent();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DestroyTime -= DeltaTime;
	if (DestroyTime < 0.0f)
	{
		Destroy();
		return;
	}

	AddActorWorldOffset(GetActorForwardVector() * DeltaTime * Speed);

}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMonster2* Mons2 = Cast<AMonster2>(OtherActor);
	if ((nullptr!= Mons2) && (OtherActor == Mons2))
	{
		// 몬스터2의 블랙보드 컴포넌트 가져오기
		UBlackboardComponent* BlackboardComp = Mons2->GetBlackboardComponent();

		if (BlackboardComp)
		{
			// 블랙보드 변수 bIsDeath를 true로 설정
			BlackboardComp->SetValueAsBool(TEXT("bIsDeath"), true);
		}
	}

	AMonster3* Mons3 = Cast<AMonster3>(OtherActor);
	if ((nullptr != Mons3) && (OtherActor == Mons3))
	{
		int a = 0;
		// 몬스터3의 블랙보드 컴포넌트 가져오기
		UBlackboardComponent* BlackboardComp = Mons3->GetBlackboardComponent();

		if (BlackboardComp)
		{
			// 블랙보드 변수 bIsDeath를 true로 설정
			BlackboardComp->SetValueAsBool(TEXT("bIsDeath"), true);
		}
	}

		ABoss* BossMons = Cast<ABoss>(OtherActor);
		if ((nullptr != BossMons) && (OtherActor == BossMons))
		{
			// 몬스터3의 블랙보드 컴포넌트 가져오기
			UBlackboardComponent* BlackboardComp = BossMons->GetBlackboardComponent();

			if (BlackboardComp)
			{
				// 블랙보드 변수 bIsDeath를 true로 설정
				BlackboardComp->SetValueAsBool(TEXT("bIsDeath"), true);
			}
		}
}

