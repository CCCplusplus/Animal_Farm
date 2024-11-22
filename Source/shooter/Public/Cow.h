// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Cow.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ACow : public AEnemy
{
	GENERATED_BODY()

public:
	ACow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
