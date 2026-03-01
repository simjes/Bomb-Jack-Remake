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
		GS->OnBombsLeftChange.AddUniqueDynamic(this, &UGameHUD::UpdateBombsLeft);
	}
}

void UGameHUD::NativeDestruct()
{
	if (ABombJackieGameState* GS = GetWorld()->GetGameState<ABombJackieGameState>())
	{
		GS->OnBombsLeftChange.RemoveDynamic(this, &UGameHUD::UpdateBombsLeft);
	}

	Super::NativeDestruct();
}

void UGameHUD::UpdateBombsLeft(const int Amount)
{
	RemainingBombsText.Get()->SetText(FText::Format(
		FText::FromString("Bombs Left: {0}"),
		Amount
	));
}
