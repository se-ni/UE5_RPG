// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAniState : uint8
{
	None, 
	Idle, //0
	LeftMove, 
	RightMove, 
	ForwardMove,  
	BackwardMove,  
	JumpStart, 
	Attack, //6
	Patrol, 
	Death,
	Hit,
	Return,
};

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	None,
	Weapon1,
	Weapon2,
	Weapon3,
};