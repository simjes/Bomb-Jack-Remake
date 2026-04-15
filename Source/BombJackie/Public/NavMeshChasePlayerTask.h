// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "NavMeshChasePlayerTask.generated.h"

class AAIController;
class AEnemyBase;
/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UNavMeshChasePlayerTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Context")
	AEnemyBase* AIPawn;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 80.0f;

	UPROPERTY()
	AAIController* AIController;

	UPROPERTY()
	ACharacter* Player;

	UPROPERTY()
	float CombinedPlayerAndAiRadius;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
	                                       const FStateTreeTransitionResult& Transition) override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

public:
	UNavMeshChasePlayerTask(const FObjectInitializer& ObjectInitializer);
};
