// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBird.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyBird::AEnemyBird()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBird::Attack_Implementation()
{
	// Call function from parent. Sets Attacking to true, sets cooldown
	Super::Attack_Implementation();

	// Get the player position to attack
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacter)
	{
		FVector Direction = PlayerCharacter->GetActorLocation() - GetActorLocation();
		Direction.Normalize(); 

		FVector LaunchVelocity = Direction * LaunchStrength;
		
		// Launch burd
		LaunchCharacter(LaunchVelocity, true, true);

		// 1 second, then stop launching
		GetWorldTimerManager().SetTimer(LaunchTimerHandle, this, &AEnemyBird::StopLaunch, 1.0f, false);
	}
}

void AEnemyBird::StopLaunch()
{
	// Stop moving and be normal burd again
	GetCharacterMovement()->StopMovementImmediately();
}
