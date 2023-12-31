// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire.h"
#include "../AI/Boss.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Stage3/MainPlayerCharacter3.h"

// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp = GetSphereComponent();
}

// Called every frame
void AFire::Tick(float DeltaTime)
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

//void AFire::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	AMainPlayerCharacter3* Player3 = Cast<AMainPlayerCharacter3>(OtherActor);
//	
//	if ((nullptr != Player3) && (OtherActor == Player3))
//	{
//		int a = 0;
//	}
//}