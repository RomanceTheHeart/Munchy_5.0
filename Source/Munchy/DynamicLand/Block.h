// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"


UENUM()
enum BlockState
{
	Healthy,
	Okay,
	NotGood,
	Damaged
};

class ADynamicFoliage;
class AMunchyGameMode;

UCLASS()
class MUNCHY_API ABlock : public AActor
{
	GENERATED_BODY()


private:
	UPROPERTY(Category = DynamicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SmartBlock = nullptr;

	UPROPERTY(Category = DynamicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BlockRoot = nullptr;

	// set the base material  for this object. 
	UPROPERTY(Category = DynamicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMaterial* BaseMaterial = nullptr;

	UPROPERTY(Category = DyanmicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMaterialInstance* OkLand = nullptr;


	UPROPERTY(Category = DyanmicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMaterialInstance* NotGoodLand = nullptr;


	UPROPERTY(Category = DyanmicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMaterialInstance* DeadLand = nullptr;

	UPROPERTY(Category = DyanmicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(Category = DyanmicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* BlockHealthComp;


	bool BisActive = false;

	UPROPERTY(Category = DyanmicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BlockLifeSpan{
		100
	};

	bool BcanSpawn{true};

	UPROPERTY(Category = DynamicBlock, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<BlockState> StateofBLock;

	FTimerHandle lifetimer;

	UWorld* BlockWorld;

	TSubclassOf<ABlock> BlockRefference;


public:
	// Sets default values for this actor's properties
	ABlock();
	FORCEINLINE BlockState GetBlockState() const { return StateofBLock; }
	FORCEINLINE BlockState SetBlockState(BlockState newstate) { return newstate = StateofBLock; }

	FORCEINLINE UStaticMeshComponent* GetSmartBlock() const { return SmartBlock; }

	FORCEINLINE USceneComponent* GetSceneComponent() const { return BlockRoot; }

	FORCEINLINE UBoxComponent* GetBoxCollision() const { return BoxCollision; }

	bool GetCanSpawn() { return BcanSpawn; }
	void SetBeCanSpawn(bool spawn) { BcanSpawn = spawn; }

	FORCEINLINE float GetBlockLifeSpan() { return BlockLifeSpan; }
	FORCEINLINE void SetBlockLifeSpan(float lifespan) { lifespan = BlockLifeSpan; }


#pragma region overlapevents

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma region overlapevents


	void BlockCountDown(float deltatime);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void UpdateBlockState();
};
