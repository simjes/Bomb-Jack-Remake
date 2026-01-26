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
		GS->OnPyramidHpChange.AddUniqueDynamic(this, &UGameHUD::UpdatePyramidHp);
	}

	if (ABombJackieCharacter* Character = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->OnHealthChanged.AddUniqueDynamic(this, &UGameHUD::UpdatePlayerHp);
	}
}

void UGameHUD::NativeDestruct()
{
	if (ABombJackieGameState* GS = GetWorld()->GetGameState<ABombJackieGameState>())
	{
		GS->OnPyramidHpChange.AddUniqueDynamic(this, &UGameHUD::UpdatePyramidHp);
	}

	if (ABombJackieCharacter* Character = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->OnHealthChanged.RemoveDynamic(this, &UGameHUD::UpdatePlayerHp);
	}
	Super::NativeDestruct();
}


void UGameHUD::UpdatePlayerHp(const int Hp)
{
	PlayerHpText.Get()->SetText(FText::Format(
		FText::FromString("Player Hp: {0}"),
		Hp
	));
}

void UGameHUD::UpdatePyramidHp(const int Hp)
{
	PyramidHpText.Get()->SetText(FText::Format(
		FText::FromString("Pyramid Hp: {0}"),
		Hp
	));
}
