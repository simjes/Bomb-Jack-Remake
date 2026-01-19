// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombJackieGameMode.h"

void ABombJackieGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GameHUDReference))
	{
		GameHUDWidget = CreateWidget(GetWorld(), GameHUDReference);
	}

	if (IsValid(GameHUDWidget))
	{
		GameHUDWidget->AddToViewport();
	}
}

ABombJackieGameMode::ABombJackieGameMode()
{
	// stub
}
