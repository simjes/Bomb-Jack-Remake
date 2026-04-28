// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBirdPatrolTask.h"
#include "EnemyBird.h"
#include "Math/UnrealMathUtility.h"

EStateTreeRunStatus UEnemyBirdPatrolTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	if (!AIPawn) return EStateTreeRunStatus::Failed;

	// Make a random vector
	FVector RandomVector = FMath::VRand();
	
	// Combine random vector with X and Y radius
	float X = RandomVector.X * AIPawn->PatrolRadius;
	float Y = RandomVector.Y * AIPawn->PatrolRadius;
	
	// Fly only above resting spot in Z axis
	float Z = FMath::Abs(RandomVector.Z / AIPawn->ZRadiusDivisor);

	// Add to resting spot
	AIPawn->TargetLocation = AIPawn->RestingLocation + FVector(X, Y, Z);

	return EStateTreeRunStatus::Succeeded;
}
