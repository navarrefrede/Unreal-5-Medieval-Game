// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtectPoint.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProtectPoint::AProtectPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProtectPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProtectPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

