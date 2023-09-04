// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Fire.generated.h"

UCLASS()
class RPG_PROJECT_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FORCEINLINE USphereComponent* GetSphereComponent()
	{
		return SphereComponent;
	}
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool GetFireOverlap()
	{
		return FireOverlap;
	}
private:
	UPROPERTY(Category = "Fire", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Speed = 1000.0f;
	UPROPERTY(Category = "Fire", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float DestroyTime = 3.0f;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent = nullptr;

	bool FireOverlap = false;

	void Setdeathbool();
	FTimerHandle bdeathTimerHandle;
};
