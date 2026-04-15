// Fill out your copyright notice in the Description page of Project Settings.


#include "NavMeshChasePlayerTask.h"

#include "AIController.h"
#include "EnemyBase.h"
#include "VectorTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

UNavMeshChasePlayerTask::UNavMeshChasePlayerTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShouldCallTick = true;
}

EStateTreeRunStatus UNavMeshChasePlayerTask::EnterState(FStateTreeExecutionContext& Context,
                                                        const FStateTreeTransitionResult& Transition)
{
	AIController = Cast<AAIController>(AIPawn->GetController());
	if (!AIController)
	{
		return EStateTreeRunStatus::Failed;
	}

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CombinedPlayerAndAiRadius = AIPawn->GetSimpleCollisionRadius() + Player->GetSimpleCollisionRadius();

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus UNavMeshChasePlayerTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	float DistanceToTarget = FVector::Dist(AIPawn->GetActorLocation(), Player->GetActorLocation()) -
		CombinedPlayerAndAiRadius;
	if (DistanceToTarget <= AcceptanceRadius && !AIPawn->Attacking)
	{
		return EStateTreeRunStatus::Succeeded;
	}

	EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(
		Player, AcceptanceRadius);
	if (MoveResult == EPathFollowingRequestResult::Type::Failed)
	{
		return EStateTreeRunStatus::Failed;
	}

	return EStateTreeRunStatus::Running;
}
