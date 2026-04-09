#include "Coin.h"

#include "BombJackieCharacter.h"
#include "VectorTypes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ACoin::ACoin()
{
	PlayerCharacter = Cast<ABombJackieCharacter>(
		UGameplayStatics::GetPlayerCharacter(this, 0)
	);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerCharacter)
	{
		OnPickupCoin.AddDynamic(PlayerCharacter, &ABombJackieCharacter::HandleCoinPickup);
	}

	GetWorldTimerManager().SetTimer(MagneticTimerHandle, [this]
	{
		IsMagnetic = true;
	}, 1, false);
}

void ACoin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(MagneticTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void ACoin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsMagnetic || !PlayerCharacter)
	{
		return;
	}

	float DistanceToPlayer = GetDistanceToPlayer();
	if (DistanceToPlayer >= MagnetRange)
	{
		return;
	}

	if (PickupMesh->IsSimulatingPhysics())
	{
		PickupMesh->SetSimulatePhysics(false);
	}

	FVector NewLocation = FMath::VInterpTo(
		GetActorLocation(),
		PlayerCharacter->GetActorLocation(),
		DeltaSeconds,
		MagnetSpeed
	);

	SetActorLocation(NewLocation);
}

void ACoin::Pickup_Implementation()
{
	Super::Pickup_Implementation();

	OnPickupCoin.Broadcast();
	Destroy();
}

float ACoin::GetDistanceToPlayer() const
{
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector Location = GetActorLocation();

	return UE::Geometry::Distance(PlayerLocation, Location);
}
