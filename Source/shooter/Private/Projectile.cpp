// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;

	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movement"));
	projectile->InitialSpeed = 5000;
	projectile->MaxSpeed = 10000;

	projectile->OnProjectileStop.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::OnHit(const FHitResult& hi)
{
	this->Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

