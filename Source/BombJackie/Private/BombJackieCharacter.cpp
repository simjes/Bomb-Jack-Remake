// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombJackieCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "BombJackie.h"
#include "BombJackieGameState.h"
#include "MusicManager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ABombJackieCharacter::BeginPlay()
{
	Super::BeginPlay();
	LastSafeLocation = GetActorLocation();

	if (ABombJackieGameState* GameState = Cast<ABombJackieGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		MusicManager = GameState->GetMusicManager();
	}
}

void ABombJackieCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(SuperStateTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void ABombJackieCharacter::EndSuperState()
{
	bIsInSuperState = false;

	if (SpawnedGlitter)
	{
		SpawnedGlitter->Deactivate();
	}

	DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), 0.0f);
	DynamicMaterial = nullptr;

	if (MusicManager)
	{
		MusicManager->ResetMusicSpeed();
	}

	EndFloat();
}

void ABombJackieCharacter::HandleEnterSuperState()
{
	CoinCount = CoinCount - CoinsRequiredForSuperState;
	bIsInSuperState = true;

	if (MusicManager)
	{
		MusicManager->SpeedUpMusic();
	}

	if (SuperStateSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SuperStateSound);
	}

	USkeletalMeshComponent* CharacterMesh = GetMesh();
	DynamicMaterial = CharacterMesh->CreateDynamicMaterialInstance(0);
	DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), 0.8f);

	if (SuperGlitter)
	{
		SpawnedGlitter = UNiagaraFunctionLibrary::SpawnSystemAttached(
			SuperGlitter,
			CharacterMesh,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::Type::KeepRelativeOffset,
			false
		);
	}

	GetWorldTimerManager().SetTimer(SuperStateTimerHandle, this, &ABombJackieCharacter::EndSuperState,
	                                SuperStateDuration, false);
}

ABombJackieCharacter::ABombJackieCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

FGenericTeamId ABombJackieCharacter::GetGenericTeamId() const
{
	return TeamId;
}

void ABombJackieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jump pressed
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
		                                   &ABombJackieCharacter::OnJumpButtonPressed);

		// Jump held — fires every frame while held
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this,
		                                   &ABombJackieCharacter::OnJumpButtonHeld);

		// Jump released
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
		                                   &ABombJackieCharacter::OnJumpButtonReleased);


		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABombJackieCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this,
		                                   &ABombJackieCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABombJackieCharacter::Look);
	}
	else
	{
		UE_LOG(LogBombJackie, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ABombJackieCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ABombJackieCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ABombJackieCharacter::Landed(const FHitResult& Hit)
{
	//reset bools used for hover stuff
	bDoubleJumpUsed = false;
	bJumpButtonHeld = false;
	if (bIsHoverActive)
	{
		bIsHoverActive = false;
		OnHoverCancel();
	}

	UClass* HitActorClass = Hit.GetActor()->GetClass();

	bool IsUnsafeLocation = UnsafeLocations.ContainsByPredicate(
		[HitActorClass, &Hit](const UObject* UnsafeLocation)
		{
			if (const UClass* ParentClass = Cast<UClass>(UnsafeLocation))
			{
				return HitActorClass->IsChildOf(ParentClass);
			}

			if (const UStaticMesh* UnsafeMesh = Cast<UStaticMesh>(UnsafeLocation))
			{
				if (const UStaticMeshComponent* MeshComponent = Hit.GetActor()->FindComponentByClass<
					UStaticMeshComponent>())
				{
					return MeshComponent->GetStaticMesh() == UnsafeMesh;
				}
			}

			return false;
		});

	if (!IsUnsafeLocation)
	{
		LastSafeLocation = Hit.Location;
	}

	Super::Landed(Hit);
}

void ABombJackieCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ABombJackieCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ABombJackieCharacter::HandleCoinPickup()
{
	CoinCount++;

	if (bIsInSuperState)
	{
		CoinCount = FMath::Min(CoinCount, 99);
	}

	if (CoinCount >= CoinsRequiredForSuperState)
	{
		HandleEnterSuperState();
	}
}

//Hover friendly jump function, which tracks if the button is held
void ABombJackieCharacter::OnJumpButtonPressed()
{
	bJumpButtonHeld = true;
	Jump();
}

//Hover friendly StopJumping function, which tracks if the button is held
void ABombJackieCharacter::OnJumpButtonReleased()
{
	bJumpButtonHeld = false;
	StopJumping();

	// Cancel hover if it was active
	if (bIsHoverActive)
	{
		bIsHoverActive = false;
		OnHoverCancel();
	}
}

void ABombJackieCharacter::OnJumpButtonHeld()
{
	if (bDoubleJumpUsed &&
		GetCharacterMovement()->IsFalling() &&
		GetVelocity().Z <= 0.0f)
	{
		if (!bIsHoverActive)
		{
			// FIRST FRAME — activate hover
			bIsHoverActive = true;
			OnJumpHeldHoverCheck();
		}
	}
}
