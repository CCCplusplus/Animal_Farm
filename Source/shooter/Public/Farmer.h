// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/kismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Projectile.h"
#include  "kismet/GameplayStatics.h"

#include "Farmer.generated.h"

UCLASS()
class SHOOTER_API AFarmer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFarmer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int tumama;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="PlayerStats")
	int life;

	UPROPERTY(EditAnywhere, Category = "PlayerUI")
	TSubclassOf<UUserWidget> playerWidgetView;
	UUserWidget* currentWidget;

	void MoveRight(float Axis);
	void MoveFoward(float Axis);

	UFUNCTION()
	void OnBeingOverLap(UPrimitiveComponent* hitComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex, bool bFromsweep, const FHitResult& resutl);

	UPROPERTY(EditAnywhere)
	FVector pos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> bulletClone;

	void ShootBullet();

};
