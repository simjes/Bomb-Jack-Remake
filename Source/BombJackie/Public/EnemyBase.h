// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class BOMBJACKIE_API AEnemyBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	FGenericTeamId TeamId = FGenericTeamId(1);
	
public:
	// Sets default values for this character's properties
	AEnemyBase();
	
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
