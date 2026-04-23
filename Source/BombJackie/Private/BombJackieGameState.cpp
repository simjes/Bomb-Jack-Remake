// Fill out your copyright notice in the Description page of Project Settings.


#include "BombJackieGameState.h"
#include "MusicManager.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABombJackieGameState::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameState = EGameState::Playing;

	OnPyramidHpChange.Broadcast(PyramidHp);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	MusicManager = GetWorld()->SpawnActor<AMusicManager>(MusicManagerClass, SpawnParams);
}

void ABombJackieGameState::HandleGameOver()
{
	CurrentGameState = EGameState::GameOver;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5f);


	GetWorld()->GetTimerManager().SetTimer(
		PauseOnGameOverTimerHandle,
		FTimerDelegate::CreateLambda([this]()
		{
			if (GameOverWidgetReference)
			{
				GameOverWidget = CreateWidget(GetWorld(), GameOverWidgetReference);
				GameOverWidget->AddToViewport();
			}
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}),
		2.0f,
		false
	);
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

AMusicManager* ABombJackieGameState::GetMusicManager()
{
	return MusicManager;
}

void ABombJackieGameState::BroadcastBombsChanged(const int Amount)
{
	OnBombsLeftChange.Broadcast(Amount);
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
