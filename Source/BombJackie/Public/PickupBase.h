// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupInterface.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UCapsuleComponent;

UCLASS()
class BOMBJACKIE_API APickupBase : public AActor, public IPickupInterface
{
	GENERATED_BODY()

	const FName MeshName = "PickupMesh";
	const FName CollisionName = "PickupCollision";

public:
	APickupBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundConcurrency* SoundConcurrency;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* PickupCollision;

	virtual void Pickup_Implementation() override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool FromSweep,
		const FHitResult& SweepResult
	);
};
