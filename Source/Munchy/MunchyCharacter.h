// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MunchyCharacter.generated.h"


#pragma region SpecialEnums

UENUM(BlueprintType)
enum class ELogLevel : uint8
{
	ETRACE UMETA(DisplayName = "Trace"),
	EDEBUG UMETA(DisplayName = "Debug"),
	EINFO UMETA(DisplayName = "Info"),
	EWARNING UMETA(DisplayName = "Warning"),
	EERROR UMETA(DisplayName = "Error")
};


UENUM(BlueprintType)
enum class EOutput_Log : uint8
{
	EAll UMETA(DisplayName = "All levels"),
	ELOG_OUTPUT UMETA(DisplayName = "Output log"),
	ESCREEN UMETA(DisplayName = "Screen")
};


UENUM(BlueprintType)
enum class EAttackType : uint8
{
	EMELEE_FIST UMETA(DisplayName = "Melee_Fist")
};
#pragma endregion SpecialEnums


#pragma region MunchyDetails


UCLASS(config = Game)


class AMunchyCharacter : public ACharacter
{
	GENERATED_BODY()


private:
	bool isReverse{false};

	bool isPunching;

	bool canSpawn{false};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attacks, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* MunchyMeleefist;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* MunchyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attacks, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* MunchyHealth;


	/*
		Log - print a message to all the log outputs with a specific color log.
		@Params- ELogLevel Affects color.
		@Params- FString The message to  display.
	*/
	void Log(ELogLevel loglevel, FString message);
	/*
		Log- prints message to all the log outputs with a specific color of log.
		@params- LogLevel affects the color of log.
		@params- message takes in the message to display.
		@paarams- EOutput_log - All Output Log or Screen.
	*/
	void Log(ELogLevel loglevel, FString message, EOutput_Log logoutput);

#pragma endregion MunchyDetails


public:
	AMunchyCharacter();


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	bool GetIsReverse() { return isReverse; }
	void SetIsReverse(bool bisreversing) { isReverse = bisreversing; }

	UFUNCTION(BlueprintPure)
	bool GetIsPunching() const { return isPunching; }

	UFUNCTION(BlueprintCallable)
	void SetIsPunching(bool bIsPunching) { isPunching = bIsPunching; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void MunchyPunch();
	void MunchyAttack();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};
