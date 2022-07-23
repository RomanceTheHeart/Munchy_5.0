// Fill out your copyright notice in the Description page of Project Settings.


#include "Munchy/DynamicLand/DynamicFoliage.h"

// Sets default values
ADynamicFoliage::ADynamicFoliage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Grass_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DynamicGrass"));
	GrassRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GRoot"));
	RootComponent = GrassRoot;
	Grass_1->SetupAttachment(GrassRoot);
}

// Called when the game starts or when spawned
void ADynamicFoliage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADynamicFoliage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
