// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAniState : uint8
{
	None,
	Idle,
	LeftMove,
	RightMove,
	ForwardMove,
	BackwardMove,
	JumpStart,
	Attack
};