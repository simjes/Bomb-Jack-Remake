// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "EnemyBirdIdleTask.generated.h"

/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UEnemyBirdIdleTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	

	UPROPERTY(EditAnywhere, Category = "Context")
	class AEnemyBird* AIPawn;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float MinIdleTime = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float MaxIdleTime = 5.0f;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

private:
	bool bHasLanded;
	float TimeSpentIdling;
	float TargetIdleDuration;
	
};
