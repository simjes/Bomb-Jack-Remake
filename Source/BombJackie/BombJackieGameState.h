// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGameState.h"
#include "GameFramework/GameStateBase.h"
#include "BombJackieGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangePyramidHp, int, Amount);

UCLASS()
class BOMBJACKIE_API ABombJackieGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EGameState CurrentGameState = EGameState::Playing;

	UPROPERTY(EditDefaultsOnly)
	int PyramidHp = 3;

	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UUserWidget> GameOverWidgetReference;
	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UUserWidget> VictoryWidgetReference;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void HandleGameOver();

protected:
	UFUNCTION()
	virtual void HandlePlayerHpChanged(int Hp);

public:
	UPROPERTY(BlueprintAssignable)
	FOnChangePyramidHp OnPyramidHpChange;

	UFUNCTION(BlueprintCallable)
	virtual void DecreasePyramidHp(int Damage);

	UFUNCTION(BlueprintCallable)
	virtual void HandleVictory();

	UPROPERTY()
	UUserWidget* GameOverWidget;

	UPROPERTY()
	UUserWidget* VictoryWidget;
};
