// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "EnemyBirdEnsureFlyingTask.generated.h"

/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UEnemyBirdEnsureFlyingTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Context")
	class AEnemyBird* AIPawn;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
