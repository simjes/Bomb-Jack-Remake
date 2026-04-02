

#include "NavMeshRoamTask.h"
#include "EnemyBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "StateTreeExecutionTypes.h"
#include "Navigation/PathFollowingComponent.h"

EStateTreeRunStatus UNavMeshRoamTask::EnterState(FStateTreeExecutionContext& Context,
                                                 const FStateTreeTransitionResult& Transition)
{
	AAIController* AIController = Cast<AAIController>(AIPawn->GetController());
	if (!AIController)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(AIPawn->GetWorld());
	if (!NavigationSystem)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	FNavLocation NewRandomLocation;
	NavigationSystem->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), RoamRadius,NewRandomLocation);
	
	EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(NewRandomLocation, AcceptanceRadius);
	if (MoveResult == EPathFollowingRequestResult::Type::Failed)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	return EStateTreeRunStatus::Succeeded;
}
