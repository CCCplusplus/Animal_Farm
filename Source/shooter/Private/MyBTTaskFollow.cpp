// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskFollow.h"

UMyBTTaskFollow::UMyBTTaskFollow()
{
}

EBTNodeResult::Type UMyBTTaskFollow::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* nodeMemory)
{
	if (APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) 
	{
		auto blackboard = Owner.GetBlackboardComponent();
		blackboard->SetValueAsObject(playerkey.SelectedKeyName, player);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
