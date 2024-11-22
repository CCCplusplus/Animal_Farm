// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Dog.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ADog : public AEnemy
{
	GENERATED_BODY()

public:
	
	ADog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
