// Copyright Epic Games, Inc. All Rights Reserved.

#include "MunchyCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Munchy/Components/HealthComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMunchyCharacter


AMunchyCharacter::AMunchyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	MunchyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MunchySkeletalMesh"));
	MunchyMesh->SetupAttachment(RootComponent);


	MunchyHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("MHealthComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMunchyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Punch", IE_Released, this, &AMunchyCharacter::MunchyPunch);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMunchyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMunchyCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMunchyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMunchyCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMunchyCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMunchyCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMunchyCharacter::OnResetVR);
}

void AMunchyCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMunchyCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMunchyCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMunchyCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMunchyCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMunchyCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward.
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation);
		AddMovementInput(Direction, Value);

		FRotator currentrotation = GetActorRotation();
		FRotator newrotation = currentrotation.GetInverse();
		if (Value <= 0)
		{
			SetIsReverse(true);
			if (GetIsReverse() == true)
			{
				GetCharacterMovement()->MaxWalkSpeed = Value;
			}
		}

		else { GetCharacterMovement()->MaxWalkSpeed = 600; }

		CameraBoom->SetRelativeLocationAndRotation(Direction, YawRotation);
	}
}

void AMunchyCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = UKismetMathLibrary::GetRightVector(YawRotation);
		// add movement in that direction
		FRotator NewRotation = GetCameraBoom()->GetTargetRotation();
		AddMovementInput(Direction, Value);
		TurnAtRate(Value * 003.f);
		SetActorRotation(YawRotation.Clamp());

		CameraBoom->SetRelativeLocationAndRotation(Direction, NewRotation);
	}
}

void AMunchyCharacter::MunchyPunch()
{
	if (!isPunching)
	{
		GetCharacterMovement()->MaxWalkSpeed = (600 / 03);
		SetIsPunching(true);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = (600);
		SetIsPunching(false);
	}
}


void AMunchyCharacter::MunchyAttack()
{
	Log(ELogLevel::EINFO, __FUNCTION__);
}


void AMunchyCharacter::Log(ELogLevel loglevel, FString message)
{
	Log(loglevel, message, EOutput_Log::EAll);
}

void AMunchyCharacter::Log(ELogLevel loglevel, FString message, EOutput_Log logoutput)
{
	if (logoutput == EOutput_Log::EAll || logoutput == EOutput_Log::ESCREEN && GEngine)
	{
		FColor logcolor = FColor::Blue;
		// Flip the color based on the type
		switch (loglevel)
		{
		case ELogLevel::ETRACE:
			logcolor = FColor::Green;
			break;

		case ELogLevel::EDEBUG:
			logcolor = FColor::Blue;
			break;

		case ELogLevel::EINFO:
			logcolor = FColor::White;
			break;

		case ELogLevel::EWARNING:
			logcolor = FColor::Red;
			break;

		default:
			break;
		}
		// print the message and leave it on screen for four seconds. 
		GEngine->AddOnScreenDebugMessage(-1, 4.5f, logcolor, message);
	}

	if (logoutput == EOutput_Log::EAll || logoutput == EOutput_Log::ELOG_OUTPUT)
	{
		switch (loglevel)
		{
		case ELogLevel::ETRACE:
			UE_LOG(LogTemp, VeryVerbose, TEXT("%s"), *message);
			break;
		case ELogLevel::EDEBUG:
			UE_LOG(LogTemp, Verbose, TEXT("%s"), *message);
			break;
		case ELogLevel::EINFO:
			UE_LOG(LogTemp, Log, TEXT("%s"), *message);
			break;
		case ELogLevel::EWARNING:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
			break;
		case ELogLevel::EERROR:
			UE_LOG(LogTemp, Error, TEXT("%s"), *message);
			break;
		default:
			UE_LOG(LogTemp, Log, TEXT("%s"), *message);
			break;
		}
	}
}
