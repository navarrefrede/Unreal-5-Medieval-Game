// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"

UCLASS()
class MEDIEVALTOWERDEFENSE_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacter();

	UFUNCTION(BlueprintCallable)
	bool GetAttack() { return bAttack; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	class USkeletalMeshComponent* MeshRef;

	void MoveForward(float value);
	void MoveSide(float value);
	void LookSide(float value);
	void LookUp(float value);
	void CrouchPressed();
	void CrouchReleased();
	void SprintPressed();
	void SprintReleased();
	void AttackPressed();
	void AttackReleased();

	void CrouchSlide(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool bCrouching;
	bool bSprinting;
	bool bRunningFWD;
	bool bRunningBWD;
	bool bRunningLeft;
	bool bRunningRight;
	bool bAttack;

	class UCharacterMovementComponent* MovementComponent;

	FVector MeshLocation;

	FVector MeshCrouchLocation;

	float CrouchStartSpeed;
	float CrouchEndSpeed;
	float SprintSpeed;
	float NormalWalkSpeed;

	float CrouchSlideTimeElapsed;
	float CrouchSlideTime;
	float NormalCrouchSpeed;
	float AttackTimer;


};
