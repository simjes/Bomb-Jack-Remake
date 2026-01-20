// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "BombJackieGameState.h"
#include "Components/TextBlock.h"

void UGameHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ABombJackieGameState* GS = GetWorld()->GetGameState<ABombJackieGameState>())
	{
		GS->OnCountDown.BindUObject(this, &UGameHUD::UpdateCountDown);
		GS->OnIncreaseScore.BindUObject(this, &UGameHUD::UpdateScore);
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
