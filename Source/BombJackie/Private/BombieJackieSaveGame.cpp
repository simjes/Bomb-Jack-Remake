// Fill out your copyright notice in the Description page of Project Settings.


#include "BombieJackieSaveGame.h"

#include "GlobalConstants.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

UBombieJackieSaveGame* UBombieJackieSaveGame::LoadGameSettings()
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->LoadSettings();

	bool SaveGameExist = UGameplayStatics::DoesSaveGameExist(SettingsSaveSlot, 0);
	if (!SaveGameExist)
	{
		return SaveGameSettings(1.0f, 1.0f, false, false);
	}

	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(SettingsSaveSlot, 0);
	if (!SaveGame)
	{
		return SaveGameSettings(1.0f, 1.0f, false, false);
	}

	UBombieJackieSaveGame* BombieJackieSaveGame = Cast<UBombieJackieSaveGame>(SaveGame);
	if (!BombieJackieSaveGame)
	{
		return SaveGameSettings(1.0f, 1.0f, false, false);
	}

	return BombieJackieSaveGame;
}

UBombieJackieSaveGame* UBombieJackieSaveGame::SaveGameSettings(float MusicValue, float SFXValue, bool ShowFPSValue,
                                                               bool VSyncValue)
{
	UBombieJackieSaveGame* SaveGame = Cast<UBombieJackieSaveGame>(
		UGameplayStatics::CreateSaveGameObject(StaticClass())
	);

	SaveGame->MusicVolume = MusicValue;
	SaveGame->SFXVolume = SFXValue;
	SaveGame->ShowFPSCounter = ShowFPSValue;
	SaveGame->VSyncEnabled = VSyncValue;

	UGameplayStatics::SaveGameToSlot(SaveGame, SettingsSaveSlot, 0);

	return SaveGame;
}
