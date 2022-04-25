// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALTOWERDEFENSE_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAI();
protected:
	virtual void BeginPlay() override;

	class AActor* ProtectPoint;

public:

	virtual void Tick(float DeltaTime) override;

private:
	
};
