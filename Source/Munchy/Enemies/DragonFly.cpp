// Fill out your copyright notice in the Description page of Project Settings.

#include "Munchy/Enemies/DragonFly.h"
#include "Misc/App.h"
#include "Engine/Classes/Engine/World.h"
#include "Munchy/DynamicLand/Block.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADragonFly::ADragonFly()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ADragonFly::BeginPlay()
{
	Super::BeginPlay();
}

// Used to set the current mode of the dragonfly. (Might expand more)


void ADragonFly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// create an are to fly


//else if (PositionToMoveto == locationtofly)
//{
//	//bIsFlying = false;

//	//PositionToMoveto = locationtofly;

//	//MaxDragonflySpeed = 0;

//	//DragonCapsule->SetSimulatePhysics(false);
//	//PositionToMoveto = ((locationtofly)+runtime) * GetFlightSpeed();


//	Hover(deltatime);
//}
