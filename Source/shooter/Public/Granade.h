// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Granade.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AGranade : public AProjectile
{
	GENERATED_BODY()
	
	AGranade();

	void OnHit(const FHitResult& hi);
};
