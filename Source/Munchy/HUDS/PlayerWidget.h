// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class MUNCHY_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPlayerWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Editanywhere, BlueprintReadWrite, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	class UProgressBar* HealthBar;
};
