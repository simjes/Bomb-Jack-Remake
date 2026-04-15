#include "EnemyAttackTask.h"

#include "EnemyBase.h"


EStateTreeRunStatus UEnemyAttackTask::EnterState(FStateTreeExecutionContext& Context,
                                                 const FStateTreeTransitionResult& Transition)
{
	IAttackInterface::Execute_Attack(AIPawn);
	return EStateTreeRunStatus::Succeeded;
}
