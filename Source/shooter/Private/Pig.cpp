// Fill out your copyright notice in the Description page of Project Settings.


#include "Pig.h"

APig::APig()
{
	PrimaryActorTick.bCanEverTick = true;
	ShouldDie = false;
}

void APig::BeginPlay()
{
	Super::BeginPlay();

	life = 100;
	Attack = 10;
}
