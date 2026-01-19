// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameHUD.h"
#include "GameFramework/GameModeBase.h"
#include "BombJackieGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ABombJackieGameMode : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UUserWidget> GameHUDReference = nullptr;

public:
	/** Constructor */
	ABombJackieGameMode();

	UPROPERTY()
	UUserWidget* GameHUDWidget;
};
