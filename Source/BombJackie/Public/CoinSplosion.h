// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSplosion.generated.h"

class USoundBase;

UCLASS()
class BOMBJACKIE_API ACoinSplosion : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoinSplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int NumberOfCoinsToSpawn;

	// Making a slot to plug in the coin in UE editor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> CoinClass;

	// Making a slot to plug in the sound in UE editor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* CoinFountainSound;
};
