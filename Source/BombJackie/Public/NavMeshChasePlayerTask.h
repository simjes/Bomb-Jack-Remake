// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "NavMeshChasePlayerTask.generated.h"

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
	float AcceptanceRadius = 100.0f;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
