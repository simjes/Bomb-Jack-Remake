// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "EnemyAttackTask.generated.h"

class AEnemyBase;
/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UEnemyAttackTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 80.0f;

	UPROPERTY(EditAnywhere, Category = "Context")
	AEnemyBase* AIPawn;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
	                                       const FStateTreeTransitionResult& Transition) override;
};
