// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DragonFly.generated.h"


UCLASS()
class MUNCHY_API ADragonFly : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ADragonFly();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
};
