#include "Enemy.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	life = 100;
	Attack = 10;
	ShouldDie = false;
}

void AEnemy::TakeDamage(int DamageAmount)
{
	life -= DamageAmount;

	if (life <= 0 && !ShouldDie) 
	{
		ShouldDie = true;
		Die();  
	}
	
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemy::Die()
{
	Destroy();
}

int AEnemy::GetAttack()
{
	return Attack;
}


void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
