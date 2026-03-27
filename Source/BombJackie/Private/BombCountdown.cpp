// Fill out your copyright notice in the Description page of Project Settings.


#include "BombCountdown.h"

#include "Bomb.h"
#include "Kismet/GameplayStatics.h"

void UBombCountdown::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = GetWorld()->GetFirstPlayerController();
	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
}

float UBombCountdown::CalculateArrowRotation(float DrawPositionX, float DrawPositionY, FVector2D& TargetScreenPosition)
{
	FVector2D Dir = (TargetScreenPosition - FVector2D(DrawPositionX, DrawPositionY)).GetSafeNormal();

	if (Dir.IsNearlyZero())
	{
		return 0.f;
	}

	float AngleRadians = FMath::Atan2(Dir.Y, Dir.X);
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

	// Arrow points down by default
	float FinalRotation = AngleDegrees - 90.f;

	return FinalRotation;
}

FCountdownRenderResult UBombCountdown::GetDrawPosition(ABomb* Bomb)
{
	if (!Controller || !CameraManager)
	{
		return FCountdownRenderResult();
	}
	
	FVector BombLocation = Bomb->GetActorLocation();
	FVector CameraLocation = CameraManager->GetCameraLocation();
	
	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(Controller, BombLocation, ScreenPosition, true);
	
	FVector ToTarget = (BombLocation - CameraLocation).GetSafeNormal();
	FVector CameraForward = CameraManager->GetCameraRotation().Vector();
	
	bool IsBehindCamera = FVector::DotProduct(CameraForward, ToTarget.GetSafeNormal()) < 0;
	
	int ScreenWidth = 0;
	int ScreenHeight = 0;
	Controller->GetViewportSize(ScreenWidth, ScreenHeight);
	
	FVector2D ScreenCenter = FVector2D(ScreenWidth * 0.5f, ScreenHeight * 0.5f); 
	
	bool IsOnScreen =
		ScreenPosition.X >= 0 && ScreenPosition.X <= ScreenWidth &&
		ScreenPosition.Y >= 0 && ScreenPosition.Y <= ScreenHeight;
	
	float DrawPositionX;
	float DrawPositionY;
	
	if (IsBehindCamera)
	{
		FVector CameraRight = CameraManager->GetActorRightVector();

		float RightDot = FVector::DotProduct(CameraRight, ToTarget);

		DrawPositionX = ScreenCenter.X + RightDot * (ScreenWidth * 0.45f);
		DrawPositionY = ScreenHeight * 0.95f;
		
		// Rotation irrelevant for this state, we just render it downwards
		return FCountdownRenderResult(FVector2D(DrawPositionX, DrawPositionY), 0, ERenderResult::CameraBehind);
	}
	
	if (IsOnScreen)
	{
		DrawPositionX = ScreenPosition.X;
		DrawPositionY = ScreenPosition.Y;
		
		// Rotation irrelevant for this state, we don't render the arrow
		return FCountdownRenderResult(FVector2D(DrawPositionX, DrawPositionY), 0, ERenderResult::InPlayerView);
	}
	
	FVector2D FromCenter = ScreenPosition - ScreenCenter;
	FVector2D Direction = FromCenter.GetSafeNormal();
	DrawPositionX = ScreenCenter.X + Direction.X * (ScreenWidth * 0.45f);
	DrawPositionY = ScreenCenter.Y + Direction.Y * (ScreenHeight * 0.45f);
	
	float Rotation = CalculateArrowRotation(DrawPositionX, DrawPositionY, ScreenPosition);
	
	return FCountdownRenderResult(FVector2D(DrawPositionX, DrawPositionY), Rotation, ERenderResult::CameraInFront);
}
