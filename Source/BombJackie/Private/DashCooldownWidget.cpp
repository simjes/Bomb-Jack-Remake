// Fill out your copyright notice in the Description page of Project Settings.


#include "DashCooldownWidget.h"

void UDashCooldownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsVisible())
	{
		if (DashCooldownRemaining > 0.0f)
		{
			DashCooldownRemaining -= InDeltaTime;
			DashCooldownRemaining = FMath::Max(DashCooldownRemaining, 0.0f);

			Progress = FMath::Clamp(1.0f - (DashCooldownRemaining / DashCooldown), 0.0f, 1.0f);
		}
	}
}

void UDashCooldownWidget::RestartDashCooldown(float Cooldown)
{
	DashCooldown = Cooldown;
	DashCooldownRemaining = DashCooldown;
	Progress = 0.f;
}
