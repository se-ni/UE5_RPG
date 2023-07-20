// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAniState : uint8
{
	None,
	Idle, //0
	LeftMove, //1
	RightMove, //2
	ForwardMove,  //3
	BackwardMove,  //4
	JumpStart, //5
	Attack //6
};

UENUM(BlueprintType)
enum class AIAniState : uint8
{
	None,
	Idle,
	Move,
	Return,
	Ratrol,
	Attack,
	Death
};