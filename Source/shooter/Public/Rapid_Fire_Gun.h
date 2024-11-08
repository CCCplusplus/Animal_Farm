// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/kismetSystemLibrary.h"
#include "Rapid_Fire_Gun.generated.h"

UCLASS()
class SHOOTER_API ARapid_Fire_Gun : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARapid_Fire_Gun();

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
