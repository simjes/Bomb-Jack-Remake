// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGameState.h"
#include "GameFramework/GameStateBase.h"
#include "BombJackieGameState.generated.h"

/**
 * 
 */


DECLARE_DELEGATE_OneParam(FOnIncreaseScore, int)
DECLARE_DELEGATE_OneParam(FOnCountDown, int)

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
	virtual void CountDown();

protected:
	UFUNCTION()
	virtual void HandleIncreaseScore(int Points);

	UFUNCTION()
	virtual void HandleDecreaseTime(int Seconds);

public:
	FOnIncreaseScore OnIncreaseScore;
	FOnCountDown OnCountDown;
};
