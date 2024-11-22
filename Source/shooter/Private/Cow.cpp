// Fill out your copyright notice in the Description page of Project Settings.


#include "Cow.h"

ACow::ACow()
{
	PrimaryActorTick.bCanEverTick = true;
	ShouldDie = false;
}

void ACow::BeginPlay()
{
	Super::BeginPlay();

	life = 200;
	Attack = 50;
}
