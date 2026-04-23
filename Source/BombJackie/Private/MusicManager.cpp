// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"

#include "BombieJackieSaveGame.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();

	if (!MasterSoundMix || !MusicSoundClass || !SFXSoundClass || !GameTheme)
	{
		return;
	}

	UBombieJackieSaveGame* Settings = UBombieJackieSaveGame::LoadGameSettings();
	UWorld* World = GetWorld();

	UGameplayStatics::SetBaseSoundMix(World, MasterSoundMix);
	UGameplayStatics::SetSoundMixClassOverride(World, MasterSoundMix, MusicSoundClass, Settings->MusicVolume);
	UGameplayStatics::SetSoundMixClassOverride(World, MasterSoundMix, SFXSoundClass, Settings->SFXVolume);

	MusicTrack = UGameplayStatics::SpawnSound2D(World, GameTheme);
}

void AMusicManager::SpeedUpMusic()
{
	if (MusicTrack)
	{
		MusicTrack->SetPitchMultiplier(SuperStatePitch);
	}
}

void AMusicManager::ResetMusicSpeed()
{
	if (MusicTrack)
	{
		MusicTrack->SetPitchMultiplier(NormalPitch);
	}
}
