// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int life;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int maxLife;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int grandes;

	UPROPERTY(EditAnywhere, Category = "PlayerUI")
	TSubclassOf<UUserWidget> playerWidgetView;
	UUserWidget* currentWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY()
	UUserWidget* CrosshairWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> SniperScopeWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* sniperSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* quickFireSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* reloadSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* fastreloadSound;

	UUserWidget* SniperScopeWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerStats")
	bool bIsAiming;

	float OriginalWalkSpeed;

	float maxStamina;

	float normalSpeed;
	float sprintSpeed;
	float slideSpeed;

	FTimerHandle SlideTimerHandle;

	void MoveRight(float Axis);
	void MoveFoward(float Axis);

	void CycleWeapons();

	void HandleMouseWheel(float AxisValue);


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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> grandeClone;

	UPROPERTY()
	AActor* rapidFireGunActor;

	UPROPERTY()
	AActor* sniper;


	bool hasSniper;

	bool hasGun;

	bool hasKnife;

	bool sniperSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	bool gunSelected;

	bool knifeSelected;

	bool isSprinting;
	bool isSliding;

	bool SCanShoot;

	FTimerHandle TimerHandle_ShootCooldown;

	FTimerHandle TimerHandle_RayCooldown;

	void ShootBullet();

	void ShootRayTrace();

	void ThrowGranade();

	void FireWeapon();

	void StartAiming();

	void StopAiming();

	void Sprint();

	void Walk();

	void Slide();

	void StopSlide();

	void SReload();

	void QReload();
};
