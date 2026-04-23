// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MusicManager.generated.h"


UCLASS()
class BOMBJACKIE_API AMusicManager : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SuperStatePitch = 1.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float NormalPitch = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundMix* MasterSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundClass* MusicSoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundClass* SFXSoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* GameTheme;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* MusicTrack;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Events")
	void SpeedUpMusic();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void ResetMusicSpeed();
};
