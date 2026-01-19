#pragma once

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Playing = 0 UMETA(DisplayName = "Playing"),
	GameOver = 1 UMETA(DisplayName = "GameOver")
};
