// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class BOMBJACKIE_API AEnemyBase : public ACharacter, public IGenericTeamAgentInterface, public IAttackInterface
{
	GENERATED_BODY()

	FGenericTeamId TeamId = FGenericTeamId(1);
	
	FTimerHandle PlayIdleSoundsTimerHandle;
	FTimerHandle AttackCooldownTimerHandle;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool Attacking = false;
	
	AEnemyBase();

	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void Attack_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MinTimeBetweenIdleSoundPlay = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Audio")
	float MaxTimeBetweenIdleSoundPlay = 6.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* IdleSounds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* AttackSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DeathSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackCooldown = 3.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsSeeingThePlayer = false;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void PlayIdleSounds();
	void ScheduleNextIdleSound();
	void ResetAttackCooldown();
};
