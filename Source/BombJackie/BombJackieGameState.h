// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGameState.h"
#include "GameFramework/GameStateBase.h"
#include "BombJackieGameState.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIncreaseScore, int, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountDown, int, Amount);

UCLASS()
class BOMBJACKIE_API ABombJackieGameState : public AGameStateBase
{
	UPROPERTY(EditDefaultsOnly)
	EGameState CurrentGameState = EGameState::Playing;

	UPROPERTY(EditDefaultsOnly)
	int TimeLeftSeconds = 100;

	UPROPERTY(EditDefaultsOnly)
	int Score = 300;

	FTimerHandle CountdownTimerHandle;

	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void CountDown();
	virtual void HandleGameOver();

protected:
	UFUNCTION()
	virtual void IncreaseScore(int Points);

	UFUNCTION()
	virtual void DecreaseTime(int Seconds);

	UFUNCTION()
	virtual void HandleHitPoints(int HitPoints);

public:
	UPROPERTY(BlueprintAssignable)
	FOnIncreaseScore OnIncreaseScore;
	UPROPERTY(BlueprintAssignable)
	FOnCountDown OnCountDown;
};
