// Fill out your copyright notice in the Description page of Project Settings.


#include "Dog.h"

ADog::ADog() 
{
	PrimaryActorTick.bCanEverTick = true;
	ShouldDie = false;
}

void ADog::BeginPlay()
{
	Super::BeginPlay();

	life = 120;
	Attack = 20;
}
