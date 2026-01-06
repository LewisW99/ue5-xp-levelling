// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnLevelUp,
	int32,
	NewLevel
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPELLTEST_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UXPComponent();

	UFUNCTION(BlueprintCallable)
	void AddXP(int32 XPToAdd);

	UPROPERTY(BlueprintAssignable)
	FOnLevelUp OnLevelUp;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentXP = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 XPPerLevel = 100;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentLevel;

	UPROPERTY(BlueprintReadOnly)
	int32 SkillPoints = 0;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SpendSkillPoints() { if (SkillPoints > 0) SkillPoints--; UE_LOG(LogTemp,Warning, TEXT( "Spent Skill Points, Skill Points Left : %i" ), SkillPoints) }

	void HandleLevelUp();
private:
	
	UFUNCTION(BlueprintCallable)
	bool CanLevelUp() const;
	
};
