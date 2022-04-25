// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"
#include "ProtectPoint.h"

AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	ProtectPoint = UGameplayStatics::GetActorOfClass(GetWorld(), AProtectPoint::StaticClass());
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProtectPoint)
	{
	MoveToLocation(ProtectPoint->GetActorLocation());
	}
}
