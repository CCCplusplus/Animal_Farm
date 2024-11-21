// Fill out your copyright notice in the Description page of Project Settings.


#include "Granade.h"

AGranade::AGranade() 
{
	projectile->InitialSpeed = 1000;
	projectile->MaxSpeed = 2000;


	projectile->OnProjectileStop.AddDynamic(this, &AGranade::OnHit);

}

void AGranade::OnHit(const FHitResult& hi)
{
	this->Destroy();
}