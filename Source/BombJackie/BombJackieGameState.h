// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGameState.h"
#include "GameFramework/GameStateBase.h"
#include "BombJackieGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangePyramidHp, int, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeBombsLeft, int, Amount);

UCLASS()
class BOMBJACKIE_API ABombJackieGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EGameState CurrentGameState = EGameState::Playing;

	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UUserWidget> GameOverWidgetReference;
	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UUserWidget> VictoryWidgetReference;

	virtual void BeginPlay() override;
	virtual void HandleGameOver();

protected:
	UPROPERTY(BlueprintReadWrite)
	int MaxPyramidHp = 3;

	UPROPERTY(BlueprintReadWrite)
	int PyramidHp = MaxPyramidHp;

public:
	UPROPERTY(BlueprintAssignable)
	FOnChangePyramidHp OnPyramidHpChange;

	UPROPERTY(BlueprintCallable)
	FOnChangeBombsLeft OnBombsLeftChange;

	UFUNCTION(BlueprintCallable)
	virtual void DecreasePyramidHp(int Damage);

	UFUNCTION(BlueprintCallable)
	virtual void HandleVictory();

	UPROPERTY()
	UUserWidget* GameOverWidget;

	UPROPERTY()
	UUserWidget* VictoryWidget;
};
