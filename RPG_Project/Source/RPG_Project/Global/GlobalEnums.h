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
	Return,
};

//UENUM(BlueprintType)
//enum class AIState : uint8
//{
//	//None, // 0
//	Idle, // 1
//	Move, // 2
//	 // 3
//	
//	Attack, // 5
//	Patrol, // 4
//	Return,
//
//};