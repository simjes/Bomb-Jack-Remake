// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBirdEnsureFlyingTask.h"
#include "EnemyBird.h"
#include "GameFramework/CharacterMovementComponent.h"

EStateTreeRunStatus UEnemyBirdEnsureFlyingTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	if (AIPawn && AIPawn->GetCharacterMovement())
	{
		AIPawn->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
	
	return EStateTreeRunStatus::Succeeded;
}
