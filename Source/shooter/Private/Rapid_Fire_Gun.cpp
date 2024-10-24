// Fill out your copyright notice in the Description page of Project Settings.


#include "Rapid_Fire_Gun.h"

// Sets default values
ARapid_Fire_Gun::ARapid_Fire_Gun()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARapid_Fire_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARapid_Fire_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hit;
	FCollisionQueryParams params;

	if (GetWorld()->LineTraceSingleByChannel(hit, GetTransform().GetLocation(), GetActorForwardVector() * 500, ECC_Visibility, params))
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetTransform().GetLocation(), GetActorForwardVector() * 500, FColor::Green);
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), hit.Location, 20, 20, FColor::Green);

		//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, hit.ToString());
	}
	else
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetTransform().GetLocation(), GetActorForwardVector() * 500, FColor::Red);
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), hit.Location, 20, 20, FColor::Red);
	}

}

// Called to bind functionality to input
void ARapid_Fire_Gun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

