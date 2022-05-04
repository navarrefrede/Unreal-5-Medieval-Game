// Fill out your copyright notice in the Description page of Project Settings.



#include "Zombie.h"
#include "Components/CapsuleComponent.h"
#include "FPCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleRef = GetCapsuleComponent();

	bCharacterAttacking = false;

	bSwordOverlap = false;

	LifeSpan = 10.f;


	
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();

	CapsuleRef->OnComponentBeginOverlap.AddDynamic(this, &AZombie::OnOverlapBegin);
	CapsuleRef->OnComponentEndOverlap.AddDynamic(this, &AZombie::OnOverlapEnd);

	BodyMesh = GetMesh();
	
}

void AZombie::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPCharacter* CharacterRef = Cast<AFPCharacter>(OtherActor);
	if (CharacterRef && Cast<USkeletalMeshComponent>(OtherComp))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sword Overlapping"));
		bSwordOverlap = true;
		if (CharacterRef->GetAttack()) 
		{
			BodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			BodyMesh->SetSimulatePhysics(true);
			BodyMesh->SetPhysicsBlendWeight(BlendWeight);
			SetLifeSpan(LifeSpan);
		}
	}
}

void AZombie::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End Called"));

	if (Cast<AFPCharacter>(OtherActor))
	{
			UE_LOG(LogTemp, Warning, TEXT("Sword not Overlapping"));
			bSwordOverlap = false;
	}
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

