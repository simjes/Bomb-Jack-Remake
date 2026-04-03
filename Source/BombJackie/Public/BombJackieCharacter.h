// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "BombJackieCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ABombJackieCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	FGenericTeamId TeamId = FGenericTeamId(0);

protected:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector LastSafeLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> UnsafeLocations;

	/** Jump button being held? */
	UPROPERTY(BlueprintReadWrite, Category = "Jump|Hover")
	bool bJumpButtonHeld = false;

	/** Double jump been used? */
	UPROPERTY(BlueprintReadWrite, Category = "Jump|Hover")
	bool bDoubleJumpUsed = false;

	UPROPERTY(BlueprintReadWrite, Category = "Jump|Hover")
	bool bIsHoverActive = false;
	
	/** Called when jump button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Jump|Hover")
	void OnJumpButtonPressed();

	/** Called when jump button is held */
	UFUNCTION(BlueprintCallable, Category = "Jump|Hover")
	void OnJumpButtonHeld();
	
	
	
	/**Event for hovering*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Jump|Hover")
	void OnJumpHeldHoverCheck();
	
	/** Called when jump button is released */
	UFUNCTION(BlueprintCallable, Category = "Jump|Hover")
	void OnJumpButtonReleased();
	
	/** Called when button released or character landed */
	UFUNCTION(BlueprintImplementableEvent, Category = "Jump|Hover")
	void OnHoverCancel();
	
public:
	/** Constructor */
	ABombJackieCharacter();
	
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	virtual void Landed(const FHitResult& Hit) override;

public:
	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);
	

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
