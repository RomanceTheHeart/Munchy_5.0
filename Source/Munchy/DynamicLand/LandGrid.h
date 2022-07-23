// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandGrid.generated.h"


class ABlock;
UCLASS()
class MUNCHY_API ALandGrid : public AActor
{
	GENERATED_BODY()


private:
	// Set timer min delay. 
	float MinSpawnDelay{1.0f};
	//Set Timer max delay. 
	float MaxSpawnDelay{4.5f};


	TArray<class ADynamicFoliage*> GrassArray;


	UPROPERTY()
	class USceneComponent* GridRoot = nullptr;


	UPROPERTY(Category = BlockToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<class AActor*> BlockArray;

	UPROPERTY(Category = BlockToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ABlock* NewBlock;

	UPROPERTY(Category = BlockToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BlockSpacing{2500};


	UPROPERTY(Category = BlockToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTransform BlockScale{FVector(.3, .3, .3)};


	UPROPERTY(Category = BlockToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 BlockAmount{0};

	UPROPERTY(Category = GrassToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ADynamicFoliage* NewGrass;

	UPROPERTY(Category = BlockToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABlock> INextBlock;

	UPROPERTY(Category = GrassToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADynamicFoliage> SpawnGrass = nullptr;


	UPROPERTY(Category = GrassToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float GrassSpacing{300};

	UPROPERTY(Category = GrassToSpawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 grassAmount{0};


public:
	// Sets default values for this actor's properties
	ALandGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetBlockAmount() { return BlockAmount; }


	FORCEINLINE class USceneComponent* GetGridRoot() const { return GridRoot; }

	FORCEINLINE class TSubclassOf<class ADynamicFoliage> GetGrass() { return SpawnGrass; }


	UFUNCTION()
	void SpawnNumBlock(int32 blockstospawn);

	UFUNCTION()
	void SpawnDynamicGrass(int32 amounttospwn);

	UFUNCTION()
	void RemoveEvenBlock();

	const TArray<FVector> GetBlockLocations();


	UPROPERTY()
	TArray<FVector> BlockPositions;
};
