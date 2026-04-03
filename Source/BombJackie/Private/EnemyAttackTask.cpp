// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackTask.h"

#include "EnemyBase.h"

EStateTreeRunStatus UEnemyAttackTask::EnterState(FStateTreeExecutionContext& Context,
                                                 const FStateTreeTransitionResult& Transition)
{
	if (!AIPawn || AIPawn->Attacking)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	IAttackInterface::Execute_Attack(AIPawn);
	
	return EStateTreeRunStatus::Succeeded;
}
