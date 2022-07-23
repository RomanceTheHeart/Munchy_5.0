// Fill out your copyright notice in the Description page of Project Settings.

#include "Munchy/DynamicLand/Block.h"
#include "Components/PrimitiveComponent.h"
#include "Munchy/DynamicLand/DynamicFoliage.h"
#include "Munchy/MunchyCharacter.h"
#include "Munchy/Enemies/DefaultDragonFly.h"
#include "Engine/TriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/Public/TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Munchy/Components/HealthComponent.h"

// Sets default values
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SmartBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnBlock"));
	BlockRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BLockRootScence"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BlockRoot;
	BlockRoot->SetAbsolute(true);
	BlockHealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("BlockHealth"));

	SmartBlock->SetupAttachment(BlockRoot);

	SmartBlock->SetMaterial(0, BaseMaterial);
	SmartBlock->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	BoxCollision->SetupAttachment(BlockRoot);
	BoxCollision->SetCollisionProfileName("Trigger");
	BoxCollision->SetRelativeScale3D(FVector(16.0f, 16.0f, 2.0f));


	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABlock::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABlock::OnOverlapEnd);
	SetActorEnableCollision(true);
}


void ABlock::BeginPlay()
{
	Super::BeginPlay();


	UpdateBlockState();
}


// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BlockCountDown(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, "Block LifeSpan: " + FString::FromInt(GetBlockLifeSpan()));
}


void ABlock::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                            class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	if (OtherComp && OtherComp != BlockRoot && OverlappedComp != BlockRoot)
	{
		ADefaultDragonFly* overlappingfly = Cast<ADefaultDragonFly>(OtherActor);

		if (overlappingfly->CurrentWayPointIndex >= 3)
		{
			overlappingfly->CurrentWayPointIndex = 0;
		}

		overlappingfly->CurrentWayPointIndex++;
	}
}


void ABlock::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                          class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp)
	{
	}
}


void ABlock::UpdateBlockState()
{
	if (BlockLifeSpan >= 75)
	{
		SetBlockState(Healthy);
		SmartBlock->SetMaterial(0, BaseMaterial);
	}

	if (BlockLifeSpan <= 50)
	{
		SetBlockState(Okay);
		SmartBlock->SetMaterial(0, OkLand);
	}
	if (BlockLifeSpan <= 25)
	{
		SetBlockState(NotGood);
		SmartBlock->SetMaterial(0, NotGoodLand);
	}
	if (BlockLifeSpan == 0)
	{
		SetBlockState(Damaged);
		SmartBlock->SetMaterial(0, DeadLand);
	}
}


void ABlock::BlockCountDown(float deltatime)
{
	if (BlockLifeSpan > 0)
	{
		BlockLifeSpan = FMath::Max(0.0f, BlockLifeSpan - deltatime);
	}
	UpdateBlockState();
}
