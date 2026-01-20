// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombJackieGameMode.h"

void ABombJackieGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GameHUDReference)
	{
		GameHUDWidget = CreateWidget(GetWorld(), GameHUDReference);
	}

	if (GameHUDWidget)
	{
		GameHUDWidget->AddToViewport();
	}
}

ABombJackieGameMode::ABombJackieGameMode()
{
	// stub
}
