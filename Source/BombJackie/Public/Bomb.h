// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BombCountdown.h"
#include "NiagaraSystem.h"
#include "PickupBase.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBombExplode, ABomb*, Instigator, int, Damage);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBombDefuse, ABomb*, Instigator);

UCLASS()
class BOMBJACKIE_API ABomb : public APickupBase
{
	GENERATED_BODY()

	FTimerHandle ExplodeCountdownTimerHandle;

	UPROPERTY()
	UBombCountdown* CountdownWidget;

	UPROPERTY(EditAnywhere)
	float MinPulseScale = 0.8f;

	UPROPERTY(EditAnywhere)
	float MaxPulseScale = 1.2f;

public:
	ABomb();

	virtual void Pickup_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplodeCountdown = 15.0f;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage = 1;

	UFUNCTION(BlueprintCallable)
	void LightFuse();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMesh* LitBombMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UNiagaraSystem* ExplodeNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<UCameraShakeBase> ExplodeCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* FuseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ExplodeSound;

	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UBombCountdown> CountdownWidgetClass;

public:
	virtual void Tick(float DeltaTime) override;
	void Explode();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBombExplode OnBombExplode;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBombDefuse OnBombDefuse;
};
