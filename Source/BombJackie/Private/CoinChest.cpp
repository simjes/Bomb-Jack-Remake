// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinChest.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "BombJackieCharacter.h"

// Sets default values
ACoinChest::ACoinChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// turning this off for now to see if we can make it work without
	PrimaryActorTick.bCanEverTick = false;
	
	// Initialize Chest mesh
	ChestComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chest"));
	RootComponent = ChestComponent;
	
}

void ACoinChest::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// check if chest is already blown
	if (HasExploded)
	{
		return;
	}

	// cast to character
	ABombJackieCharacter* JackieCharacter = Cast<ABombJackieCharacter>(Other);
	
	if (JackieCharacter)
	{
		// dash check
		if (JackieCharacter->IsDashing) 
		{
			
			HasExploded = true;

			// CoinSplosion location 50 pikksels above chest origin
			FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
			FRotator SpawnRotation = FRotator::ZeroRotator;

			// Spawn dat Splosion <3
			if (CoinSplosionClass)
			{
				FActorSpawnParameters SpawnParams;
				// Always spawn, ignore collisions
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
				
				GetWorld()->SpawnActor<AActor>(CoinSplosionClass, SpawnLocation, SpawnRotation, SpawnParams);
			}

			// Audio
			if (ChestBreakSound)
			{
				// Playing the sound in the world so it doesn't get destroyed with the actor
				UGameplayStatics::PlaySoundAtLocation(this, ChestBreakSound, GetActorLocation());
			}

			// actor destruction
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ACoinChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

