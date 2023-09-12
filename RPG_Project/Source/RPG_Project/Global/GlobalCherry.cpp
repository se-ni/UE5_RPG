// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalCherry.h"

// Sets default values
AGlobalCherry::AGlobalCherry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalCherry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobalCherry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

