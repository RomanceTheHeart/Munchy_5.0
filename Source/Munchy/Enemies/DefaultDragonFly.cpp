// Fill out your copyright notice in the Description page of Project Settings.


#include "Munchy/Enemies/DefaultDragonFly.h"

#include <ratio>

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Munchy/DynamicLand/Block.h"
#include "Kismet/KismetSystemLibrary.h"
#include	"Kismet/KismetMathLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ADefaultDragonFly::ADefaultDragonFly()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//DragonScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));


	DragonSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DragonCollision"));

	DragonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DragonSkeletion"));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("DragonMovement"));

	RootComponent = DragonSphere;


	//DragonSphere->SetupAttachment(RootComponent);
	DragonMesh->SetupAttachment(DragonSphere);

	MaxDragonflySpeed = Movement->MaxSpeed;

	FlightSpeed = 0;
	MaxDragonflySpeed = 1500;
	FlightSpeed = MaxDragonflySpeed;
	Movement->SetActive(true);

	flightTime = maxFlightTime;

	SetMode(ScavengerMode::SEARCHFRUIT);
}

// Called when the game starts or when spawned
void ADefaultDragonFly::BeginPlay()
{
	Super::BeginPlay();
}


void ADefaultDragonFly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetFlightTimer(GetFlightTime(), DeltaTime);
	ResetTimer();
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Green, ("Flight Time: " + FString::FromInt(GetFlightTime())));
}


void ADefaultDragonFly::Hover(float& deltatime)
{
	FVector NewLocation = GetActorLocation();

	FRotator NewRotation = GetActorRotation();

	int32 newscale = FMath::RandRange(3, 6);

	float RunningTime = GetGameTimeSinceCreation();


	float DeltaHeight = (FMath::Sin(RunningTime + deltatime) - FMath::Sin(RunningTime));

	NewLocation.Z += DeltaHeight * newscale; //Scale our height by a factor of 20

	float DeltaRotation = deltatime * 3000.0f; //Rotate by 20 degrees per second

	NewRotation.Yaw += DeltaRotation;

	SetActorLocation(NewLocation);
}


#pragma region Logic


void ADefaultDragonFly::FlyToLocation(FVector location, float deltatime)
{
	SetIsFlying(true);
	Thisflylocation = this->GetActorLocation();


	constexpr float distance{10};

	Distancetotarget = (Thisflylocation - location).Size() * distance;
	
	constexpr float maxDistance{100.0f};

	const float ratio = (Distancetotarget < maxDistance) ? Thisflylocation.Size() / distance : 1.0f;

	const float currentDistance = maxDistance * ratio;






	

	{
		if (currentDistance < Distancetotarget )
		{
			

			location = (location - Thisflylocation);
			
			SetActorRotation(location.Rotation());
			MoveFoward(deltatime);


			GEngine->AddOnScreenDebugMessage(-1, 300.f, FColor::Orange,
			                                 ("Block distance from : " + FString::FromInt(Distancetotarget)));
		}


		else if (Thisflylocation.Size() == Distancetotarget)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, (TEXT("At Location..")));
			ThrustDisEngage(deltatime);
		}
	}
}


float ADefaultDragonFly::SetFlightTimer(float time, float deltatime)
{
	time = GetFlightTime();

	const float runtime = GetGameTimeSinceCreation();

	if (time <= maxFlightTime)
	{
		time = FMath::Max(0.0f, time - (deltatime));

		SetFlightTime(time);
	}


	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, ("Flight Time: " + FString::FromInt(GetFlightTime())));

	return time;
}

void ADefaultDragonFly::ResetTimer()
{
	if (GetFlightTime() == 0)
	{
		SetFlightTime(maxFlightTime);
	}
}
#pragma endregion Logic


#pragma  region Control


void ADefaultDragonFly::Roll(float deltatime)
{
	float alpha{-1.0f};
	float runtime = GetGameTimeSinceCreation();
	float axisvalue = (alpha > 0) ? 1.0f : -1.0f;
	axisvalue *= airControl;
	FVector rightDirection = DragonSphere->GetRightVector() * axisvalue;
	//FVector mergevector = FMath::VInterpTo(FVector(0.0f, 0.0f, 0.0f), rightDirection, (runtime - deltatime), .01);
	DragonSphere->AddTorqueInDegrees(rightDirection, FName("None"), true);
}


void ADefaultDragonFly::Pitch(float deltatime)
{
	float alpha{1.0f};
	float axisvalue = (alpha > 0) ? 1.0f : -1.0f;
	axisvalue *= airControl;
	FVector fowardDirection = DragonSphere->GetForwardVector() * axisvalue;
	//FVector mergedvector = FMath::VInterpTo(FVector(0.0f, 0.0f, 0.0f), fowardDirection, deltatime, .01);
	DragonSphere->AddTorqueInDegrees(fowardDirection, FName("None"), true);
}


void ADefaultDragonFly::MoveFoward(float deltatime)
{
	float thruttleup = ThrustEngage(deltatime);


	FVector velocity = DragonSphere->GetForwardVector();


	if (bthrustEngage == true)
	{
		velocity *= thrustValue * 100.0f;


		DragonSphere->AddForce(velocity * DragonSphere->GetMass());
	}


	/*FVector mergedvector = FMath::VInterpTo(FVector(0.0f, 0.0f, 0.0f), velocity, deltatime, .1);

	DragonSphere->SetPhysicsLinearVelocity(mergedvector);

	SetThrustValue(0.0f);*/
}


void ADefaultDragonFly::MoveRight(float deltatime)
{
	float alpha{1.0f};

	float axisvalue = (alpha > 0) ? 1.0f : -1.0f;
	axisvalue *= airControl;
	FVector upDirection = DragonSphere->GetUpVector() * axisvalue;
	FVector mergedvector = FMath::Lerp(FVector(0.0f, 0.0f, 0.0f), upDirection, axisvalue);
	DragonSphere->AddTorqueInDegrees(mergedvector, FName("None"), true);
}


#pragma region Thrust


float ADefaultDragonFly::ThrustEngage(float deltatime)
{
	float alpha{0};
	float runtime = GetGameTimeSinceCreation();

	for (float i{0}; i <= thrustValue; ++i)
	{
		if (alpha <= thrustValue)
		{
			alpha = FMath::Min(thrustValue, ((alpha + 1.0f) * (runtime + deltatime)) / 2);
		}
	}


	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, (TEXT("SPEED: ") + FString::FromInt(alpha)));

	return alpha;
}


float ADefaultDragonFly::ThrustDisEngage(float deltatime)
{
	float alpha = GetThrustValue();
	float runtime = GetGameTimeSinceCreation();

	FVector velocity = DragonSphere->GetPhysicsLinearVelocity();
	if (alpha > 0)
	{
		for (float i{alpha}; i >= alpha; --i)
		{
			alpha = FMath::Max(0.0f, thrustValue -= (runtime + deltatime));
		}
	}


	if (alpha <= 0)
	{
		alpha = 0;
	}
	FVector mergedvector = FMath::VInterpTo(FVector(0.0f, 0.0f, 0.0f), velocity, deltatime, .1);

	DragonSphere->SetPhysicsLinearVelocity(mergedvector);

	SetThrustValue(0.0f);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, (TEXT("SPEED: ") + FString::FromInt(alpha)));
	return alpha;
}


#pragma endregion Thrust


#pragma endregion Control
