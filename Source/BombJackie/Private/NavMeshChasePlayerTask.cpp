// Fill out your copyright notice in the Description page of Project Settings.


#include "NavMeshChasePlayerTask.h"

#include "AIController.h"
#include "EnemyBase.h"
#include "VectorTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

EStateTreeRunStatus UNavMeshChasePlayerTask::EnterState(FStateTreeExecutionContext& Context,
                                                 const FStateTreeTransitionResult& Transition)
{
	AAIController* AIController = Cast<AAIController>(AIPawn->GetController());
	if (!AIController)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(Player, AcceptanceRadius);
	if (MoveResult == EPathFollowingRequestResult::Type::Failed)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	float DistanceToTarget = UE::Geometry::Distance(AIPawn->GetActorLocation(), Player->GetActorLocation());
	if (DistanceToTarget <= AcceptanceRadius)
	{
		return EStateTreeRunStatus::Succeeded;
	}
	
	return EStateTreeRunStatus::Failed;
}
