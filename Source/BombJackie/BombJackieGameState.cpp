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

	if (ABombJackieCharacter* Character = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->OnHealthChanged.AddUniqueDynamic(this, &ABombJackieGameState::HandlePlayerHpChanged);
	}
}

void ABombJackieGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ABombJackieCharacter* Character = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->OnHealthChanged.RemoveDynamic(this, &ABombJackieGameState::HandlePlayerHpChanged);
	}

	Super::EndPlay(EndPlayReason);
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

void ABombJackieGameState::HandlePlayerHpChanged(const int Hp)
{
	if (Hp == 0)
	{
		HandleGameOver();
	}
}
