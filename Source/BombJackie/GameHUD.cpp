// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "BombJackieCharacter.h"
#include "BombJackieGameState.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ABombJackieGameState* GS = GetWorld()->GetGameState<ABombJackieGameState>())
	{
		GS->OnCountDown.BindUObject(this, &UGameHUD::UpdateCountDown);
		GS->OnIncreaseScore.BindUObject(this, &UGameHUD::UpdateScore);
	}

	if (ABombJackieCharacter* Character = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->OnHealthChanged.AddUniqueDynamic(this, &UGameHUD::UpdateHitPoints);
		// TODO: unbind on end?
	}
}

void UGameHUD::BeginDestroy()
{
	Super::BeginDestroy();

	if (ABombJackieCharacter* Character = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->OnHealthChanged.RemoveDynamic(this, &UGameHUD::UpdateHitPoints);
	}
}

void UGameHUD::UpdateScore(const int Score) const
{
	ScoreText.Get()->SetText(FText::Format(
		FText::FromString("Score: {0}"),
		Score
	));
}

void UGameHUD::UpdateCountDown(const int TimeSeconds) const
{
	CountdownText.Get()->SetText(FText::Format(
		FText::FromString("Time: {0}"),
		TimeSeconds
	));
}

void UGameHUD::UpdateHitPoints(const int HitPoints)
{
	HitPointsText.Get()->SetText(FText::Format(
		FText::FromString("HP: {0}"),
		HitPoints
	));
}
