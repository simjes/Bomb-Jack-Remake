// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DashCooldownWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UDashCooldownWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	float DashCooldown = 0;

	UPROPERTY()
	float DashCooldownRemaining = 0;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Progress = 0;

public:
	void RestartDashCooldown(float Cooldown);
};
