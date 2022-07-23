// Fill out your copyright notice in the Description page of Project Settings.


#include "Munchy/AI/EnemyAI.h"
#include "Munchy/DynamicLand/LandGrid.h"
#include "Munchy\DynamicLand\Block.h"
#include "Munchy/Enemies/DefaultDragonFly.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet\KismetMathLibrary.h"
#include "Tasks/AITask_MoveTo.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Blueprint\AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine\World.h"
#include "EngineUtils.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "Navigation/PathFollowingComponent.h"


AEnemyAI::AEnemyAI()
{

	PrimaryActorTick.bCanEverTick = true;


}



void AEnemyAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);



}




void AEnemyAI::BeginPlay()

{


	Super::BeginPlay();

	AIDragonFly = Cast<ADefaultDragonFly>(GetPawn());

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlock::StaticClass(), blockactors);

	int32 NumTargets = blockactors.Num();



	//NextBlock = Cast<ABlock>(GetPawn());


	for (TActorIterator<ABlock> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		NextBlock = *actorItr;


		FVector bLockLocation_1 = NextBlock->GetRootComponent()->GetChildComponent(1)->GetComponentLocation();

		FVector bLockLocation_2 = NextBlock->GetActorLocation();

		bLockLocation_1.BoundToCube(3.0f);

		PositionToFlyTo.AddUnique(bLockLocation_1);


	}



}





void AEnemyAI::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);




	
	MoveToWayPoints(PositionToFlyTo, DeltaTime);




}





TArray<FVector>AEnemyAI::MoveToWayPoints(const TArray<FVector>& positions, float deltatime)
{


	TArray<FVector> output = positions;

	int32 pointToGo = AIDragonFly->CurrentWayPointIndex;

	for (const FVector& newpositions : output)

	{
		if (output.Contains(newpositions) && AIDragonFly->GetMode() == ScavengerMode::CASEPLAYER)

		{
			AIDragonFly->FlyToLocation(output[pointToGo], deltatime);
		}



		else if (output.Contains(newpositions) && AIDragonFly->GetMode() == ScavengerMode::SEARCHFRUIT)
		{
			AIDragonFly->FlyToLocation(output[pointToGo], deltatime);

		}





		else {
			MoveToNextBlockLocation(output, deltatime);
		}



	}




	GEngine->AddOnScreenDebugMessage(-1, 300.f, FColor::Yellow, ("Current Block_Index: " + FString::FromInt(AIDragonFly->CurrentWayPointIndex)));

	return output;

}



void AEnemyAI::MoveToNextBlockLocation(const TArray<FVector>& positions, float deltatime)
{

	for (FVector pos : positions)
	{

		int32 pointToGo = positions.Num() - 1;



		if (pointToGo)


			//GEngine->AddOnScreenDebugMessage(-1, 300.f, FColor::Orange, ("Points to go : " + FString::FromInt(pointToGo)));

			if (pointToGo >= positions.Num() - 1)
			{
				pointToGo = 0;

			}


			else
				pointToGo++;

	}

}
