// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BombCountdown.generated.h"

class ABomb;

UENUM(BlueprintType)
enum class ERenderResult : uint8
{
	InPlayerView = 0 UMETA(DisplayName = "InPlayerView"),
	// It can be in front of the camera without being in the players view
	CameraInFront = 1 UMETA(DisplayName = "CameraInFront"),
	CameraBehind = 2 UMETA(DisplayName = "CameraBehind")
};

USTRUCT(BlueprintType)
struct FCountdownRenderResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector2D DrawPosition;

	UPROPERTY(BlueprintReadOnly)
	float ArrowRotation;

	UPROPERTY(BlueprintReadOnly)
	ERenderResult RenderResult;
};

/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UBombCountdown : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	APlayerCameraManager* CameraManager;
	
	UPROPERTY()
	APlayerController* Controller;
	
	virtual void NativeConstruct() override;
	
	float CalculateArrowRotation(float DrawPositionX, float DrawPositionY, FVector2D& TargetScreenPosition);
	
public:
	UFUNCTION(BlueprintCallable)
	FCountdownRenderResult GetDrawPosition(ABomb* Bomb);
};
