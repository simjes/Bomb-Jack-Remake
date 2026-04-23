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
		return SaveGameSettings(1.0f, 1.0f);
	}

	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(SettingsSaveSlot, 0);
	if (!SaveGame)
	{
		return SaveGameSettings(1.0f, 1.0f);
	}

	UBombieJackieSaveGame* BombieJackieSaveGame = Cast<UBombieJackieSaveGame>(SaveGame);
	if (!BombieJackieSaveGame)
	{
		return SaveGameSettings(1.0f, 1.0f);
	}

	return BombieJackieSaveGame;
}

UBombieJackieSaveGame* UBombieJackieSaveGame::SaveGameSettings(float MusicValue, float SFXValue)
{
	UBombieJackieSaveGame* SaveGame = Cast<UBombieJackieSaveGame>(
		UGameplayStatics::CreateSaveGameObject(StaticClass())
	);

	SaveGame->MusicVolume = MusicValue;
	SaveGame->SFXVolume = SFXValue;

	UGameplayStatics::SaveGameToSlot(SaveGame, SettingsSaveSlot, 0);

	return SaveGame;
}
