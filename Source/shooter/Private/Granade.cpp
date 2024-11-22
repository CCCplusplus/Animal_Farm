// Fill out your copyright notice in the Description page of Project Settings.


#include "Granade.h"
#include "Dog.h"
#include "Cow.h"
#include "Pig.h"
#include "Farmer.h"
#include "Math/UnrealMathUtility.h"

AGranade::AGranade() 
{
	projectile->InitialSpeed = 1000;
	projectile->MaxSpeed = 2000;


	projectile->OnProjectileStop.AddDynamic(this, &AGranade::OnHit);

}

void AGranade::OnHit(const FHitResult& hi)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hit something"));
    TArray<AActor*> AffectedActors;
    FVector ExplosionCenter = hi.ImpactPoint;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);  

    
    const int NumRays = 1000;  
    const float Radius = 500;  
    for (int i = 0; i < NumRays; ++i)
    {
        
        FVector Direction = FMath::VRand();
        FVector End = ExplosionCenter + Direction * Radius;

        FHitResult HitResult;
        if (GetWorld()->LineTraceSingleByChannel(HitResult, ExplosionCenter, End, ECC_Visibility, Params))
        {
            AActor* HitActor = HitResult.GetActor();
            if (HitActor && !AffectedActors.Contains(HitActor))
            {
                
                if (ADog* HitDog = Cast<ADog>(HitActor))
                {
                    HitDog->TakeDamage(50);
                    AffectedActors.Add(HitDog);
                }
                else if (ACow* HitCow = Cast<ACow>(HitActor))
                {
                    HitCow->TakeDamage(50);
                    AffectedActors.Add(HitCow);
                }
                else if (APig* HitPig = Cast<APig>(HitActor))
                {
                    HitPig->TakeDamage(50);
                    AffectedActors.Add(HitPig);
                }
                else if (AFarmer* HitChara = Cast<AFarmer>(HitActor)) 
                {
                    HitChara->life -= 50;
                    AffectedActors.Add(HitChara);
                }
            }
        }
        DrawDebugLine(GetWorld(), ExplosionCenter, End, FColor::Red, false, 2.0f, 0, 1.0f);
    }

    
    this->Destroy();
}

void AGranade::BeginPlay()
{
	Super::BeginPlay();

}
