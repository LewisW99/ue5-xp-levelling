// Fill out your copyright notice in the Description page of Project Settings.


#include "XPComponent.h"


// Sets default values for this component's properties
UXPComponent::UXPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UXPComponent::AddXP(int32 XPAmount)
{
	CurrentXP += XPAmount;

	UE_LOG(LogTemp, Log, TEXT("Added XP: %d"), XPAmount);

	while (CanLevelUp())
	{
		HandleLevelUp();
	}
}

void UXPComponent::HandleLevelUp()
{
	CurrentXP -= XPPerLevel;
	XPPerLevel += 10;
	CurrentLevel++;
	SkillPoints++;

	OnLevelUp.Broadcast(CurrentLevel);
	UE_LOG(LogTemp, Log, TEXT("New Level: %d"), CurrentLevel);
}


bool UXPComponent::CanLevelUp() const
{
	UE_LOG(LogTemp, Log, TEXT("CanLevelUp: %i"), CurrentXP);

	
	return CurrentXP >= XPPerLevel;
	
}




