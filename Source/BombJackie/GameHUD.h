// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateScore(int Score);
	UFUNCTION(BlueprintCallable)
	void UpdateCountDown(int TimeSeconds);
	UFUNCTION(BlueprintCallable)
	void UpdateHitPoints(int HitPoints);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> CountdownText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> HitPointsText;
};
