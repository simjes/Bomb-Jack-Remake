// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BombieJackieSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UBombieJackieSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graphics")
	bool VSyncEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graphics")
	bool ShowFPSCounter = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	float MusicVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	float SFXVolume = 1.0f;

	UFUNCTION(BlueprintCallable)
	static UBombieJackieSaveGame* LoadGameSettings();

	UFUNCTION(BlueprintCallable)
	static UBombieJackieSaveGame*
	SaveGameSettings(float MusicValue, float SFXValue, bool ShowFPSValue, bool VSyncValue);
};
