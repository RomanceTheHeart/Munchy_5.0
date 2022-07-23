// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DefaultDragonFly.generated.h"


UENUM(BlueprintType)
enum class ScavengerMode : uint8
{
	SEARCHFRUIT UMETA(Display = "SEARCHFRUIT"),
	CASEPLAYER UMETA(Display = "CHASEPLAYER")
};


UCLASS()
class MUNCHY_API ADefaultDragonFly : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultDragonFly();


protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;


public:
	// Called every frame

	virtual void Tick(float DeltaTime) override;


public:
#pragma region navigation

	UPROPERTY(Category = ScavengerMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CurrentWayPointIndex{
		0
	};

	FORCEINLINE void SetPositionToMove(FVector position) { position = PositionToMoveto; }

	FORCEINLINE bool GetIsAtPoint() { return bIsAtPoint; }

	FORCEINLINE bool SetIsAtPoint(bool isat)
	{
		bIsAtPoint = isat;
		return isat;
	}

	void FlyToLocation(FVector location, float deltatime);

#pragma endregion


#pragma region flight


	FORCEINLINE bool SetIsFlying(bool isflying)
	{
		bIsFlying = isflying;
		return isflying;
	}

	FORCEINLINE bool IsFlying() { return bIsFlying; }

	FORCEINLINE void SetMode(ScavengerMode state) { Mode = state; }

	FORCEINLINE float GetThrustValue() { return thrustValue; }

	FORCEINLINE float SetThrustValue(float newvalue)
	{
		thrustValue = newvalue;
		return newvalue;
	}

	void Hover(float& deltatime);

	float ThrustEngage(float deltatime);


	float ThrustDisEngage(float delttime);


	void Roll(float deltatime);

	void Pitch(float deltatime);

	void MoveFoward(float deltatime);

	void MoveRight(float deltatime);


#pragma endregion flight


	float SetFlightTimer(float time, float deltatime);

	void ResetTimer();


	ScavengerMode& GetMode() { return Mode; }

	float GetFlightTime() const { return this->flightTime; }
	float SetFlightTime(float time) { return this->flightTime = time; }

private:
	UPROPERTY(Category = Flight, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsAtPoint{false};

	UPROPERTY(Category = Flight, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float thrustValue{300};

	UPROPERTY(Category = Flight, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float flightTime{0.0f};


	UPROPERTY(Category = Flight, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float maxFlightTime{10.0f};
	UPROPERTY(Category = Flight, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 airControl{
		500
	};

	UPROPERTY(Category = ScavengerMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DistanceBeforeArrivedAtWaypoint{5.0f};

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ScavengerMode Mode = ScavengerMode::SEARCHFRUIT;

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FlightSpeed;

	UPROPERTY(Category = DragonMode, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxDragonflySpeed;

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ChaseSpeed{500.f};


	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector PositionToMoveto;

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DistanceBeforeArrivingAt{100};

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsAtWayPoint{false};

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bVelocityChange{false};

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsFlying{false};

	UPROPERTY(Category = DragonMode, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bthrustEngage{true};


	UPROPERTY(Category = DragonComponents, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* DragonSphere;


	UPROPERTY(Category = DragonComponents, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* DragonMesh;

	UPROPERTY(Category = DragonComponents, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DragonScene;

	UPROPERTY(Category = DragonComponents, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* Movement;

	UPROPERTY(Category = DragonFlyLife, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 DragonlifeSpan{
		10
	};

	UPROPERTY(Category = DragonFlySight, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 TraceDistance{
		30
	};

	FVector Thisflylocation = {0, 0, 0};

	float Distancetotarget{0};
};
