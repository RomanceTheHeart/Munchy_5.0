// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicFoliage.generated.h"

UCLASS()
class MUNCHY_API ADynamicFoliage : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Foliage, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Grass_1 = nullptr;

	UPROPERTY(Category = Foliage, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* GrassRoot = nullptr;


public:
	// Sets default values for this actor's properties
	ADynamicFoliage();

	UStaticMeshComponent* GetGrass() { return Grass_1; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
