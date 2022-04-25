// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates object for the camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	MeshRef = GetMesh();

	MeshRef->SetupAttachment(Camera);

	// Reference to the character movement component
	MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());

	//Floats

	NormalWalkSpeed = 600.f;

	MovementComponent->MaxWalkSpeed = NormalWalkSpeed;

	SprintSpeed = 1.5 * NormalWalkSpeed;

	CrouchSlideTime = 0.4f;

	CrouchSlideTimeElapsed = CrouchSlideTime;

	NormalCrouchSpeed = MovementComponent->MaxWalkSpeedCrouched;

	// NOT BEING USED

	CrouchHeight = 40.f;

	NormalHeight = 88.f;

	CrouchHeightSpeed = 4.f;
	
	MovementComponent->CrouchedHalfHeight = CrouchHeight;

	// Booleans
	bCrouching = false;
	bRunningFWD = false;
	bRunningBWD = false;
	bRunningLeft = false;
	bRunningRight = false;
	bSprinting = false;


} 

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CrouchSlide(DeltaTime);

}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPCharacter::CrouchPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFPCharacter::CrouchReleased);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPCharacter::SprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPCharacter::SprintReleased);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AFPCharacter::MoveSide);
	PlayerInputComponent->BindAxis("LookSide", this, &AFPCharacter::LookSide);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPCharacter::LookUp);

}

void AFPCharacter::MoveForward(float value)
{
	// Sets booleans for direction
	// Will use in first person animations
	if (value < -0.9f)
	{
		bRunningFWD = false;
		bRunningBWD = true;
	}
	if (value > 0.9f)
	{
		bRunningFWD = true;
		bRunningBWD = false;
	}
	if (value < 0.9 && value > -0.9)
	{
		bRunningFWD = false;
		bRunningBWD = false;
	}

	AddMovementInput(GetActorForwardVector() * value);
}

void AFPCharacter::MoveSide(float value)
{
	// Sets booleans for direction
	// Will use in first person animations
	if (value < -0.9f)
	{
		bRunningRight = false;
		bRunningLeft = true;
	}
	if (value > 0.9f)
	{
		bRunningRight = true;
		bRunningLeft = false;
	}
	if (value < 0.9 && value > -0.9)
	{
		bRunningRight = false;
		bRunningLeft = false;
	}

	AddMovementInput(GetActorRightVector() * value);
}

void AFPCharacter::LookSide(float value)
{
	AddControllerYawInput(value);
}

void AFPCharacter::LookUp(float value)
{
	AddControllerPitchInput(-value);
}

void AFPCharacter::CrouchPressed()
{
	bCrouching = true;
	CrouchSlideTimeElapsed = 0.f;
	Crouch();
	
}

void AFPCharacter::CrouchReleased()
{
	bCrouching = false;
	UnCrouch();
}

void AFPCharacter::SprintPressed()
{
	bSprinting = true;
	MovementComponent->MaxWalkSpeed = SprintSpeed;
}

void AFPCharacter::SprintReleased()
{
	bSprinting = false;
	MovementComponent->MaxWalkSpeed = NormalWalkSpeed;
}

void AFPCharacter::CrouchSlide(float DeltaTime)
{
	if (CrouchSlideTimeElapsed < CrouchSlideTime && bSprinting && bCrouching)
	{
		MovementComponent->MaxWalkSpeedCrouched = FMath::Lerp(SprintSpeed, NormalCrouchSpeed, CrouchSlideTimeElapsed / CrouchSlideTime);
		CrouchSlideTimeElapsed += DeltaTime;
	}
}

// Doesn't Work :(
void AFPCharacter::SmoothCrouchHeight(float DeltaTime)
{
	// Crouch height won't lerp as the crouch funciton seems to take what ever the crouch half height is at whenever function is called

	if (CrouchHeightTimeElapsed < CrouchHeightSpeed && bCrouching)
	{
		MovementComponent->SetCrouchedHalfHeight(FMath::Lerp(NormalHeight, CrouchHeight, CrouchHeightTimeElapsed / CrouchHeightSpeed));
		Crouch();
		CrouchHeightTimeElapsed += DeltaTime;
	}


	UE_LOG(LogTemp, Warning, TEXT("CrouchHeightTimeElapsed: %f"), CrouchHeightTimeElapsed);
	UE_LOG(LogTemp, Warning, TEXT("CrouchHeight: %f"), MovementComponent->CrouchedHalfHeight);
}
