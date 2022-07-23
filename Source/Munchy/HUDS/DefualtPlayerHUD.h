// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "DefualtPlayerHUD.generated.h"

/**
 *
 */
UCLASS()
class MUNCHY_API ADefualtPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> HealthDisplayClass;

	virtual void BeginPlay() override;

private:
	class UPlayerWidget* HealthDisplay;
};
