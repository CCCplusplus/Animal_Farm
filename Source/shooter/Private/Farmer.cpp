// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer.h"

// Sets default values
AFarmer::AFarmer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	normalSpeed = 500.0f;
	sprintSpeed = 750.0f;
	slideSpeed = 900.0f;

	GetCapsuleComponent()->InitCapsuleSize(40, 96);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300;
	cameraBoom->bUsePawnControlRotation = true;

	cameraBoom->SocketOffset = FVector(0.0f, 100.0f, 0.0f);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;

	maxLife = 100;
	life = maxLife;
	grandes = 3;
	ammo = 0;
	maxStamina = 100;
	stamina = maxStamina;
	hasSniper = false;
	hasGun = false;
	hasKnife = false;

	gunSelected = true;
	sniperSelected = false;
	knifeSelected = false;

	bIsAiming = false;

	isSprinting = false;
	isSliding = false;

	SCanShoot = false;
}

void AFarmer::MoveRight(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AFarmer::MoveFoward(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
}

void AFarmer::CycleWeapons()
{
	int availableWeapons = (hasSniper ? 1 : 0) + (hasGun ? 1 : 0) + (hasKnife ? 1 : 0);

	if (availableWeapons <= 1) return;

	if (sniperSelected && hasGun)
	{
		sniperSelected = false;
		gunSelected = true;
		knifeSelected = false;
	}
	else if (gunSelected && hasKnife)
	{
		sniperSelected = false;
		gunSelected = false;
		knifeSelected = true;
	}
	else if (knifeSelected && hasSniper)
	{
		sniperSelected = true;
		gunSelected = false;
		knifeSelected = false;
	}
	else if (sniperSelected && !hasGun && hasKnife)
	{
		sniperSelected = false;
		gunSelected = false;
		knifeSelected = true;
	}
	else if (knifeSelected && !hasSniper && hasGun)
	{
		sniperSelected = false;
		gunSelected = true;
		knifeSelected = false;
	}
	else if (gunSelected && !hasKnife && hasSniper)
	{
		sniperSelected = true;
		gunSelected = false;
		knifeSelected = false;
	}

}


void AFarmer::HandleMouseWheel(float AxisValue)
{
	if (AxisValue != 0.0f)
		CycleWeapons();
}


void AFarmer::OnBeingOverLap(UPrimitiveComponent* hitComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex, bool bFromsweep, const FHitResult& resutl)
{
	if (other->ActorHasTag("obj")) {
		if (life < maxLife) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, "GetObj");
			life += 25;
			other->Destroy();
		}
	}
	
	if (other->ActorHasTag("rapid_fire_gun") && !hasGun)
	{
		hasGun = true;
		rapidFireGunActor = other;
		other->SetActorEnableCollision(false);
		ammo = 12;
		sniperSelected = false;
		knifeSelected = false;
		gunSelected = true;
	}

	if (other->ActorHasTag("Sniper") && !hasSniper)
	{
		hasSniper = true;
		sniper = other;
		other->SetActorEnableCollision(false);
		SCanShoot = true;
		gunSelected = false;
		knifeSelected = false;
		sniperSelected = true;
	}
}

void AFarmer::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AFarmer::OnBeingOverLap);

	if (playerWidgetView != nullptr) {
		currentWidget = CreateWidget(GetWorld(), playerWidgetView);
		currentWidget->AddToViewport();
	}

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		if (CrosshairWidget)
			CrosshairWidget->AddToViewport();
	}

}

// Called every frame
void AFarmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (hasGun && rapidFireGunActor)
	{
		if (gunSelected)
			rapidFireGunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r_weapon_socket"));

		else
			rapidFireGunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("spine_03Socket"));
	}

	if (hasSniper && sniper)
	{
		if (sniperSelected)
			sniper->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r_weapon_socket"));
		else
			sniper->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("spine_03Socket"));
	}

	if (isSprinting)
	{
		if (stamina > 0)
		{
			stamina -= DeltaTime * 20;
			if (stamina <= 0)
			{
				stamina = 0;
				Walk();
			}
		}
	}
	else if (stamina < maxStamina)
	{
		stamina += DeltaTime * 10;
		if (stamina > maxStamina)
			stamina = maxStamina;
	}

	if (life > maxLife)
		life = maxLife;
}

// Called to bind functionality to input
void AFarmer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Look Up", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Move Foward", this, &AFarmer::MoveFoward);
	PlayerInputComponent->BindAxis("Move Right", this, &AFarmer::MoveRight);

	PlayerInputComponent->BindAxis("MouseWheel", this, &AFarmer::HandleMouseWheel);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AFarmer::FireWeapon);

	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AFarmer::ThrowGranade);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFarmer::StartAiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFarmer::StopAiming);

	PlayerInputComponent->BindAction("CycleWeapon", IE_Pressed, this, &AFarmer::CycleWeapons);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFarmer::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFarmer::Walk);

	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &AFarmer::Slide);
}

void AFarmer::ShootBullet()
{
	if (!SCanShoot || !hasSniper) return;

	if (sniperSound)
		UGameplayStatics::PlaySoundAtLocation(this, sniperSound, GetActorLocation());


	if (bulletClone)
	{
		FVector StartLocation = camera->GetComponentLocation();
		FRotator AimDirection = camera->GetComponentRotation();
		FVector MuzzleLocation = StartLocation + AimDirection.Vector() * 100.0f;

		GetWorld()->SpawnActor<AProjectile>(bulletClone, MuzzleLocation, AimDirection);
	}

	SCanShoot = false;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShootCooldown, this, &AFarmer::SReload, 1.0f, false);
}

void AFarmer::ShootRayTrace()
{
	if (!hasGun || ammo <= 0) return;

	if(quickFireSound)
		UGameplayStatics::PlaySoundAtLocation(this, quickFireSound, GetActorLocation());

	ammo--;

	if (ammo == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_RayCooldown, this, &AFarmer::QReload, 2.0f, false);
	}

	FVector Start = camera->GetComponentLocation();
	FVector ForwardVector = camera->GetForwardVector();

	Start += ForwardVector * 50.0f;

	FVector End = Start + (ForwardVector * 10000.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);


	FColor LineColor = bHit ? FColor::Green : FColor::Red;


	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 1.0f);

	if (bHit)
		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 12, FColor::Green, false, 2.0f);
	else
		DrawDebugSphere(GetWorld(), End, 10.0f, 12, FColor::Red, false, 2.0f);
}

void AFarmer::ThrowGranade()
{
	if (grandes < 1) return;

	if (grandeClone)
	{
		FVector MuzzleLocation = GetMesh()->GetSocketLocation(FName("Muzzle"));

		FRotator CameraRotation = camera->GetComponentRotation();

		GetWorld()->SpawnActor<AProjectile>(grandeClone, MuzzleLocation, CameraRotation);

		grandes -= 1;
	}
}

void AFarmer::FireWeapon()
{
	if (sniperSelected && hasSniper)
		ShootBullet();
	else if (gunSelected && hasGun)
		ShootRayTrace();
	else if (knifeSelected && hasKnife)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Knife Attack!"));
}

void AFarmer::StartAiming()
{
	bIsAiming = true;

	OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed * 0.5f;

	if (sniperSelected)
	{
		cameraBoom->TargetArmLength = 20.0f;
		camera->FieldOfView = 30.0f;

		if (SniperScopeWidgetClass && !SniperScopeWidget)
		{
			SniperScopeWidget = CreateWidget<UUserWidget>(GetWorld(), SniperScopeWidgetClass);
			if (SniperScopeWidget)
				SniperScopeWidget->AddToViewport();
		}

		if (CrosshairWidget)
			CrosshairWidget->RemoveFromViewport();
	}
	else
		cameraBoom->TargetArmLength = 200.0f;


	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AFarmer::StopAiming()
{
	bIsAiming = false;

	GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;

	cameraBoom->TargetArmLength = 300.0f;
	camera->FieldOfView = 90.0f;

	if (SniperScopeWidget)
	{
		SniperScopeWidget->RemoveFromViewport();
		SniperScopeWidget = nullptr;
	}

	if (CrosshairWidget && !CrosshairWidget->IsInViewport())
		CrosshairWidget->AddToViewport();

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AFarmer::Sprint()
{
	if (stamina > 0)
	{
		isSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	}
}

void AFarmer::Walk()
{
	isSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
}


void AFarmer::Slide()
{
	if (isSprinting && !isSliding)
	{
		isSliding = true;
		GetCharacterMovement()->MaxWalkSpeed = slideSpeed;
		GetWorld()->GetTimerManager().SetTimer(SlideTimerHandle, this, &AFarmer::StopSlide, 1.0f, false);
	}
}

void AFarmer::StopSlide()
{
	isSliding = false;
	Walk();
}

void AFarmer::SReload()
{
	if (reloadSound)
		UGameplayStatics::PlaySoundAtLocation(this, reloadSound, GetActorLocation());
	
	SCanShoot = true;
}

void AFarmer::QReload()
{
	if (fastreloadSound)
		UGameplayStatics::PlaySoundAtLocation(this, fastreloadSound, GetActorLocation());

	ammo = 12;
}

