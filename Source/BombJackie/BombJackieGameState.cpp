// Fill out your copyright notice in the Description page of Project Settings.


#include "BombJackieGameState.h"


#include "BombJackieCharacter.h"
#include "TimerManager.h"
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
	// TODO: send game over event
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Game Over"));
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

void ABombJackieGameState::HandlePlayerHpChanged(int Hp)
{
	if (Hp == 0)
	{
		HandleGameOver();
	}
}
