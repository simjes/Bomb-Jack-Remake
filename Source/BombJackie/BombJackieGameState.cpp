// Fill out your copyright notice in the Description page of Project Settings.


#include "BombJackieGameState.h"


#include "TimerManager.h"

void ABombJackieGameState::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameState = EGameState::Playing;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ABombJackieGameState::CountDown, 1.0f, true);

	OnIncreaseScore.Broadcast(Score);
	OnCountDown.Broadcast(TimeLeftSeconds);
}

void ABombJackieGameState::CountDown()
{
	ABombJackieGameState::DecreaseTime(1);
}


void ABombJackieGameState::IncreaseScore(const int Points)
{
	Score += Points;

	OnIncreaseScore.Broadcast(Score);
}

void ABombJackieGameState::DecreaseTime(const int Seconds)
{
	TimeLeftSeconds -= Seconds;
	TimeLeftSeconds = std::max(TimeLeftSeconds, 0);

	OnCountDown.Broadcast(TimeLeftSeconds);

	if (TimeLeftSeconds == 0)
	{
		CurrentGameState = EGameState::GameOver;
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		// TODO: send game over event
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Game Over"));
	}
}
