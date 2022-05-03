// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"
#include "ProtectPoint.h"
#include "Zombie.h"

AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;

	LockOnDistance = 1000.f;
	Closeness = 1.f;
	bFollowPlayer = false;

	
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	ProtectPoint = UGameplayStatics::GetActorOfClass(GetWorld(), AProtectPoint::StaticClass());
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn && ProtectPoint)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombie::StaticClass(), Zombies);

		for (int32 i = 0; i < Zombies.Num(); i++)
		{
			FVector Difference = (PlayerPawn->GetActorLocation()) - (Zombies[i]->GetActorLocation());

			float Distance = sqrt((Difference.X * Difference.X) + (Difference.Y * Difference.Y));

			if (Distance < LockOnDistance && Distance > Closeness)
			{
				MoveToLocation(PlayerPawn->GetActorLocation());
			}
			else
			{
				MoveToLocation(ProtectPoint->GetActorLocation());
			}
		}
		
	}



}
