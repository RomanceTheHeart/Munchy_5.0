// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAI.generated.h"

/**
 *
 */
UCLASS()
class MUNCHY_API AEnemyAI : public AAIController
{
	GENERATED_BODY()


private:
	UPROPERTY(Transient)
	TArray<FVector> PositionToFlyTo;

	TArray<class ABlock*> BlockArray;

	TArray<class ADragonFly*> DragonFlyArray;

	TSubclassOf<class ADragonFly> FlyClass;

	TSubclassOf<class ABlock> BlockClass;

	TSubclassOf<class ALandGrid> LandClass;

	TArray<AActor*> blockactors;
	UFUNCTION()


	TArray<FVector> MoveToWayPoints(const TArray<FVector>& positions, float deltatime);

	void MoveToNextBlockLocation(const TArray<FVector>& positions, float deltatime);

	UPROPERTY(Category = Navigation, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ADefaultDragonFly* AIDragonFly;

	UPROPERTY(Category = Navigation, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ABlock* NextBlock;

	UPROPERTY(Category = Navigation, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ALandGrid* Land;


	UPROPERTY(Category = Navigation, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float timeSpentAtLocation{0};


public:
	AEnemyAI();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;
};
