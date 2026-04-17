// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSplosion.h"
//components
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
//UE stuff
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
ACoinSplosion::ACoinSplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Compocomponents
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
	
	//nearly enough coins to get halfway to superstate
	NumberOfCoinsToSpawn = 42; 
	
}

// Called when the game starts or when spawned
void ACoinSplosion::BeginPlay()
{
	Super::BeginPlay();

	// sound is same as coin sound
	if (CoinFountainSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CoinFountainSound, GetActorLocation());
	}

	// loop for making 42 of BP_Coin
	for (int i = 0; i < NumberOfCoinsToSpawn; ++i)
	{
		// Spawn transform
		FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 40.0f);
		
		// coins go upwards
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 90.0f); 

		if (CoinClass)
		{
			// try do adjust location, but always spawn
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// spawn dat cash
			AActor* SpawnedCoin = GetWorld()->SpawnActor<AActor>(CoinClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (SpawnedCoin)
			{
				// get component by class
				UStaticMeshComponent* CoinMesh = SpawnedCoin->FindComponentByClass<UStaticMeshComponent>();
				
				if (CoinMesh)
				{
					// random unit vector, in cone shape
					FVector ConeDir = FVector::UpVector;
					float HalfAngleRad = FMath::DegreesToRadians(180.0f);
					FVector RandomDir = FMath::VRandCone(ConeDir, HalfAngleRad);
					
					// Multiply X 300.0
					FVector ImpulseVector = RandomDir * 300.0f;

					// force push
					CoinMesh->AddImpulse(ImpulseVector, NAME_None, true);
				}
			}
		}
	}

	// destroy the splosion
	Destroy();
}

// Called every frame
void ACoinSplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

