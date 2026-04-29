// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FGenericTeamId AEnemyBase::GetGenericTeamId() const
{
	return TeamId;
}

void AEnemyBase::Attack_Implementation()
{
	Attacking = true;
	GetWorldTimerManager().SetTimer(AttackCooldownTimerHandle, this, &AEnemyBase::ResetAttackCooldown, AttackCooldown, false);
	
	if (AttackSound)
	{
		UGameplayStatics::SpawnSoundAttached(AttackSound, GetMesh());
	}
}

bool AEnemyBase::HandleDeath_Implementation()
{
	
	if (DeathSound)
	{
		UGameplayStatics::SpawnSoundAttached(DeathSound, GetMesh());
	}
	
	return true; 
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	ScheduleNextIdleSound();
}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(PlayIdleSoundsTimerHandle);
	GetWorldTimerManager().ClearTimer(AttackCooldownTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void AEnemyBase::PlayIdleSounds()
{
	if (IdleSounds)
	{
		UGameplayStatics::SpawnSoundAttached(IdleSounds, GetMesh());
		
		ScheduleNextIdleSound();
	}
}

void AEnemyBase::ScheduleNextIdleSound()
{
	float IdleSoundDelay = FMath::RandRange(MinTimeBetweenIdleSoundPlay, MaxTimeBetweenIdleSoundPlay);
	GetWorldTimerManager().SetTimer(PlayIdleSoundsTimerHandle, this, &AEnemyBase::PlayIdleSounds, IdleSoundDelay, false);
}

void AEnemyBase::ResetAttackCooldown()
{
	Attacking = false;
}
