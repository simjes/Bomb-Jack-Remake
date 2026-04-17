// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinChest.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS()
class BOMBJACKIE_API ACoinChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Chest mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ChestComponent;
	
	//CoinSplosion call
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> CoinSplosionClass;
	
	//Audio
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* ChestBreakSound;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Hit event
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	// Using bool here instead of the DoOnce node we used in BP
	bool HasExploded = false;

};
