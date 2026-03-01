// Fill out your copyright notice in the Description page of Project Settings.


#include "BombJackieGameState.h"
#include "BombJackieCharacter.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABombJackieGameState::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameState = EGameState::Playing;

	OnPyramidHpChange.Broadcast(PyramidHp);
}

void ABombJackieGameState::HandleGameOver()
{
	CurrentGameState = EGameState::GameOver;

	if (GameOverWidgetReference)
	{
		GameOverWidget = CreateWidget(GetWorld(), GameOverWidgetReference);
		GameOverWidget->AddToViewport();
	}

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ABombJackieGameState::HandleVictory()
{
	if (CurrentGameState != EGameState::Playing)
	{
		// We return early if the game was lost by the last bomb exploding
		return;
	}

	CurrentGameState = EGameState::Victory;

	if (VictoryWidgetReference)
	{
		VictoryWidget = CreateWidget(GetWorld(), VictoryWidgetReference);
		VictoryWidget->AddToViewport();
	}

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ABombJackieGameState::DecreasePyramidHp(const int Damage)
{
	PyramidHp -= Damage;
	PyramidHp = std::max(PyramidHp, 0);

	OnPyramidHpChange.Broadcast(PyramidHp);

	if (PyramidHp == 0)
	{
		HandleGameOver();
	}
}
