// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "../AI/Monster2.h"
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
	OnDestroyed.AddDynamic(this, &AProjectile::DesytroyProjectile);
	
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

void AProjectile::DesytroyProjectile(AActor* _Destroy)
{
	if (nullptr == DeathCreateObject)
	{
		return;
	}

	AActor* Actor = GetWorld()->SpawnActor<AActor>(DeathCreateObject);

	Actor->SetActorLocation(GetActorLocation());
	Actor->SetActorRotation(GetActorRotation());
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AMonster2* Mons = Cast<AMonster2>(OtherActor);

	// 몬스터2의 블랙보드 컴포넌트 가져오기
	UBlackboardComponent* BlackboardComp = Mons->GetBlackboardComponent();

	if (BlackboardComp)
	{
		// 블랙보드 변수 bIsDeath를 true로 설정
		BlackboardComp->SetValueAsBool(TEXT("bIsDeath"), true);
	}
}