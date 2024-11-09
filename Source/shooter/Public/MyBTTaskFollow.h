// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"
#include "MyBTTaskFollow.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UMyBTTaskFollow : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UMyBTTaskFollow();


	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector playerkey;
	
	virtual EBTNodeResult::Type
		ExecuteTask(UBehaviorTreeComponent& Owner, uint8* nodeMemory) override;
};
