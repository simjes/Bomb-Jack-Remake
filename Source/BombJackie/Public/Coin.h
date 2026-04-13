// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "Coin.generated.h"

class ABombJackieCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupCoin);

UCLASS()
class BOMBJACKIE_API ACoin : public APickupBase
{
	GENERATED_BODY()

	UPROPERTY()
	ABombJackieCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
	float MagnetSpeed = 15;

	UPROPERTY(EditAnywhere)
	float MagnetRange = 300;

	UPROPERTY(EditAnywhere)
	bool IsMagnetic = false;

	FTimerHandle MagneticTimerHandle;

	float GetDistanceToPlayer() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

public:
	ACoin();
	virtual void Pickup_Implementation() override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPickupCoin OnPickupCoin;
};
