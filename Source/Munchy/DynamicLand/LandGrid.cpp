// Fill out your copyright notice in the Description page of Project Settings.

#include "Munchy/DynamicLand/LandGrid.h"
#include "Munchy/DynamicLand/Block.h"
#include "Munchy/DynamicLand/DynamicFoliage.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include "Kismet/BlueprintSetLibrary.h"


// Sets default values
ALandGrid::ALandGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GridRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LandGridRoot"));

	RootComponent = GridRoot;
}


// Called when the game starts or when spawned
void ALandGrid::BeginPlay()
{
	Super::BeginPlay();


	if (GetWorld())
	{
		SpawnDynamicGrass(grassAmount);
	}
}


// Called every frame
void ALandGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALandGrid::RemoveEvenBlock()
{
}


void ALandGrid::SpawnNumBlock(int32 blockstospawn)
{
	BlockAmount = blockstospawn;

	FActorSpawnParameters spawnparams;

	spawnparams.Owner = this;

	spawnparams.Instigator = GetInstigator();


	if (blockstospawn == 1)
	{
		blockstospawn = BlockArray.Num();


		for (AActor* block : BlockArray)
		{
			int32 Index{0};


			Index = BlockArray.Num();


			float x_offset = (Index / BlockArray.Num()) * BlockSpacing; //Divide by dimension. 
			float y_offset = (Index % BlockArray.Num()) * BlockSpacing;
			//Take what's left over from the x_offset calculation.

			const FVector blockloction = FVector(x_offset, y_offset, 0.0f) + GetActorLocation();


			//BlockArray.Emplace(block->GetWorld()->SpawnActor<ABlock>(INextBlock, blockloction, FRotator(0, 0, 0), spawnparams));

			block = NewObject<ABlock>(this, TEXT("DBlock"));
			block->RegisterAllComponents();

			if (!block) { return; }

			block->AttachToComponent(GridRoot, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
		}
	}


	else if (blockstospawn > 1)
	{
		blockstospawn = BlockArray.Num() * BlockArray.Num();


		for (AActor* block : BlockArray)
		{
			int32 Index{0};
			Index = BlockArray.Num();


			float x_offset = (Index / BlockArray.Num()) * BlockSpacing; //Divide by dimension. 
			float y_offset = (Index % BlockArray.Num()) * BlockSpacing;
			//Take what's left over from the x_offset calculation.

			const FVector blockloction = FVector(x_offset, y_offset, 0.0f) + GetActorLocation();

			block = NewObject<ABlock>(this, TEXT("DBlock"));
			block->RegisterAllComponents();
			//BlockArray.Emplace(block->GetWorld()->SpawnActor<ABlock>(INextBlock, blockloction, FRotator(0, 0, 0), spawnparams));

			if (!block) { return; }
			block->AttachToComponent(GridRoot, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
		}
	}
}


const TArray<FVector> ALandGrid::GetBlockLocations()
{
	for (const FVector& pos : BlockPositions)
	{
		BlockPositions.Emplace(pos);
	}


	return BlockPositions;
}


void ALandGrid::SpawnDynamicGrass(int32 amounttospawn)
{
	//todo implement wheretospawn;

	UWorld* world = GetWorld();
	grassAmount = amounttospawn;


	if (amounttospawn > 0)
	{
		FActorSpawnParameters spawnparams;
		spawnparams.Owner = this;
		spawnparams.Instigator = GetInstigator();
		NewGrass = NewObject<ADynamicFoliage>(this, ADynamicFoliage::StaticClass());

		if (!NewGrass) { return; }


		const int NumGrass = (amounttospawn * amounttospawn);
		for (int32 index_j{0}; index_j < NumGrass; index_j++)
		{
			const float grassx_offset = (index_j / amounttospawn) * GrassSpacing;
			const float grassy_offset = (index_j % amounttospawn) * GrassSpacing;
			FVector spawn = FVector(grassy_offset * .5, grassx_offset * .5, 0.0f) + this->GetActorLocation();

			if (!world) { return; }

			NewGrass = world->SpawnActor<ADynamicFoliage>(SpawnGrass, spawn, FRotator(0, 0, 0), spawnparams);

			FVector actorscale = NewGrass->GetActorScale3D();
			NewGrass->SetActorRelativeScale3D(FVector(1.0, 1.0, actorscale.Z * 3.5));
			//NewGrass->SetActorLocation(FVector(spawn.X, spawn.Y, spawn.Z * 0.55f));
			NewGrass->RegisterAllComponents();
		}
	}
}
