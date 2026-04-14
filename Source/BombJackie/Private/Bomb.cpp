#include "Bomb.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Blueprint/UserWidget.h"

ABomb::ABomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LitFuseNiagara = CreateDefaultSubobject<UNiagaraComponent>(LitFuseNiagaraName);
	LitFuseNiagara->SetupAttachment(RootComponent);
	LitFuseNiagara->SetAutoActivate(false);
}

void ABomb::Pickup_Implementation()
{
	Super::Pickup_Implementation();
	if (CountdownWidget)
	{
		CountdownWidget->RemoveFromParent();
	}

	OnBombDefuse.Broadcast(this);
	Destroy();
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	if (IsLit)
	{
		LightFuse();
	}
}

void ABomb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(ExplodeCountdownTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void ABomb::LightFuse()
{
	IsLit = true;
	PickupMesh->SetRenderCustomDepth(true);

	if (LitFuseNiagara->GetAsset())
	{
		LitFuseNiagara->Activate(true);
	}

	if (LitBombMesh)
	{
		PickupMesh->SetStaticMesh(LitBombMesh);
	}

	if (FuseSound)
	{
		UGameplayStatics::SpawnSoundAttached(FuseSound, PickupMesh, NAME_None, FVector::ZeroVector,
		                                     FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}

	if (CountdownWidgetClass)
	{
		CountdownWidget = CreateWidget<UBombCountdown>(GetWorld(), CountdownWidgetClass);
		CountdownWidget->Bomb = this;
		CountdownWidget->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(ExplodeCountdownTimerHandle, this, &ABomb::Explode, ExplodeCountdown, false);
}

void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLit)
	{
		float ScaleValue = FMath::Lerp(MinPulseScale, MaxPulseScale,
		                               (FMath::Sin(GetGameTimeSinceCreation() * 2) + 1.0f) / 2.0f);
		PickupMesh->SetRelativeScale3D(FVector(ScaleValue));
	}
}

void ABomb::Explode()
{
	OnBombExplode.Broadcast(this, Damage);

	if (CountdownWidget)
	{
		CountdownWidget->RemoveFromParent();
	}

	if (ExplodeSound)
	{
		UGameplayStatics::SpawnSoundAttached(ExplodeSound, PickupMesh);
	}

	if (ExplodeNiagara)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplodeNiagara, GetActorLocation(),
		                                               GetActorRotation());
	}

	if (ExplodeCameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ExplodeCameraShake, 1.0f,
		                                                               ECameraShakePlaySpace::World);
	}

	Destroy();
}
