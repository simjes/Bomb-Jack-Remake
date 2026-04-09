// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"

#include "BombJackieCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupBase::APickupBase()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(MeshName);
	RootComponent = PickupMesh;

	PickupCollision = CreateDefaultSubobject<UCapsuleComponent>(CollisionName);
	PickupCollision->SetupAttachment(PickupMesh);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APickupBase::Pickup_Implementation()
{
	if (PickupSound)
	{
		UGameplayStatics::PlaySound2D(
			GetWorld(),
			PickupSound,
			1,
			1,
			0,
			SoundConcurrency,
			nullptr,
			false
		);
	}
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnComponentBeginOverlap);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep,
                                          const FHitResult& SweepResult)
{
	if (Cast<ABombJackieCharacter>(OtherActor))
	{
		Execute_Pickup(this);
	}
}
