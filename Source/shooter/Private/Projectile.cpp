// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Dog.h"
#include "Cow.h"
#include "Pig.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;

	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movement"));
	projectile->InitialSpeed = 11000;
	projectile->MaxSpeed = 22000;

	projectile->OnProjectileStop.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::OnHit(const FHitResult& hi)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hit something"));
	if (hi.GetActor() != nullptr)
	{
		ADog* HitDog = Cast<ADog>(hi.GetActor());
		ACow* HitCow = Cast<ACow>(hi.GetActor());
		APig* HitPig = Cast<APig>(hi.GetActor());

		if (HitDog != nullptr)
			HitDog->TakeDamage(40);

		if (HitCow != nullptr)
			HitCow->TakeDamage(40);

		if (HitPig != nullptr)
			HitPig->TakeDamage(40);
	}
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

