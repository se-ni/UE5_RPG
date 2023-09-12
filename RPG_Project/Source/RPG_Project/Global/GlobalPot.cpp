// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalPot.h"

// Sets default values
AGlobalPot::AGlobalPot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalPot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobalPot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

