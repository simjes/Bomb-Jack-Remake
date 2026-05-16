// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyBird.generated.h"

/**
 * 
 */
UCLASS()
class BOMBJACKIE_API AEnemyBird : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AEnemyBird();

	// Burdy variables for moving and burding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird AI")
	FVector RestingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird AI")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird AI")
	int32 PatrolsDone = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird AI")
	float PatrolRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird AI")
	float ZRadiusDivisor = 2.0f;

	// Variables for evil Burd actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird AI|Combat")
	float LaunchStrength = 3000.0f;

	
	virtual void Attack_Implementation() override;

protected:
	FTimerHandle LaunchTimerHandle;

	UFUNCTION()
	void StopLaunch();
};