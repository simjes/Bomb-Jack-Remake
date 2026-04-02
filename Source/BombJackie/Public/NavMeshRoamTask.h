// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "NavMeshRoamTask.generated.h"

class AEnemyBase;
/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UNavMeshRoamTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	AEnemyBase* AIPawn;
	
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float RoamRadius = 1000.0f;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
