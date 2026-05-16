// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBirdIdleTask.h"
#include "EnemyBird.h"
#include "GameFramework/CharacterMovementComponent.h"



EStateTreeRunStatus UEnemyBirdIdleTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	// Using tick
	bShouldCallTick = true; 
	if (!AIPawn) return EStateTreeRunStatus::Failed;

	bHasLanded = false;
	TimeSpentIdling = 0.0f;
	TargetIdleDuration = FMath::RandRange(MinIdleTime, MaxIdleTime);

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus UEnemyBirdIdleTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	if (!AIPawn)
	{
		return EStateTreeRunStatus::Failed;
	}

	if (!bHasLanded)
	{
		// Check if the bird is at its resting spot
		float Distance = FVector::Dist(AIPawn->GetActorLocation(), AIPawn->RestingLocation);
		
		if (Distance <= 50.0f) 
		{
			// Reached destination, Land
			AIPawn->GetCharacterMovement()->SetMovementMode(MOVE_None);
			bHasLanded = true;
		}
		else
		{
			// Fly towards resting location
			FVector Direction = (AIPawn->RestingLocation - AIPawn->GetActorLocation()).GetSafeNormal();
			AIPawn->AddMovementInput(Direction, 1.0f);
		}
	}
	else
	{
		// Process the timer in the tick
		TimeSpentIdling += DeltaTime;
		if (TimeSpentIdling >= TargetIdleDuration)
		{
			AIPawn->PatrolsDone = 0; // Reset patrols
			return EStateTreeRunStatus::Succeeded;
		}
	}
	return EStateTreeRunStatus::Running;
}
