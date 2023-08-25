// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Projectile.generated.h"

UCLASS()
class RPG_PROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Projectile", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> DeathCreateObject = nullptr;

	UFUNCTION()
		FORCEINLINE USphereComponent* GetSphereComponent()
	{
		return SphereComponent;
	}

private:
	UPROPERTY(Category = "Projectile", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Speed = 300.0f;
	UPROPERTY(Category = "Projectile", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float DestroyTime = 5.0f;

	UFUNCTION()
	void DesytroyProjectile(AActor* _Destroy);

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent = nullptr;

};
