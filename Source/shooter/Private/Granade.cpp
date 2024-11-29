// Fill out your copyright notice in the Description page of Project Settings.


#include "Granade.h"
#include "Dog.h"
#include "Cow.h"
#include "Pig.h"
#include "Farmer.h"
#include "NiagaraSystem.h"
#include "Math/UnrealMathUtility.h"

AGranade::AGranade()
{
    projectile->InitialSpeed = 1000;
    projectile->MaxSpeed = 2000;


    projectile->OnProjectileStop.AddDynamic(this, &AGranade::OnHit);

    ExplosionEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ExplosionEffect"));
    ExplosionEffect->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraEffect(TEXT("/Game/MsvFx_Niagara_Explosion_Pack_01/Prefabs/Niagara_Explosion_01"));
    if (NiagaraEffect.Succeeded())
        ExplosionEffect->SetAsset(NiagaraEffect.Object);
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Failed."));

    ExplosionEffect->SetAutoActivate(false);

}

void AGranade::OnHit(const FHitResult& Hit)
{
    TArray<AActor*> AffectedActors;
    FVector ExplosionCenter = Hit.ImpactPoint;
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
                    AffectedActors.AddUnique(HitDog);
                }
                else if (ACow* HitCow = Cast<ACow>(HitActor))
                {
                    HitCow->TakeDamage(50);
                    AffectedActors.AddUnique(HitCow);
                }
                else if (APig* HitPig = Cast<APig>(HitActor))
                {
                    HitPig->TakeDamage(50);
                    AffectedActors.AddUnique(HitPig);
                }
                else if (AFarmer* HitChara = Cast<AFarmer>(HitActor))
                {
                    HitChara->life -= 50;
                    AffectedActors.AddUnique(HitChara);
                }
            }
        }
        /*DrawDebugLine(GetWorld(), ExplosionCenter, End, FColor::Red, false, 2.0f, 0, 1.0f);*/
    }

    if (ExplosionEffect)
    {
        ExplosionEffect->SetWorldLocation(ExplosionCenter + (ExplosionCenter.YAxisVector + 20));
        ExplosionEffect->ActivateSystem();
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Failed 2"));

    this->Destroy();
}

void AGranade::BeginPlay()
{
    Super::BeginPlay();

}