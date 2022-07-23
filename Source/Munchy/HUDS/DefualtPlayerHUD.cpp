// Fill out your copyright notice in the Description page of Project Settings.


#include "Munchy/HUDS/DefualtPlayerHUD.h"
#include "Munchy/HUDS/PlayerWidget.h"
#include "Blueprint/UserWidget.h"

void ADefualtPlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	if (HealthDisplayClass)
	{
		HealthDisplay = CreateWidget<UPlayerWidget>(GetWorld(), HealthDisplayClass);
		if (HealthDisplay)
		{
			HealthDisplay->AddToViewport();
		}
	}
}
