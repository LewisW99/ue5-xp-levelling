// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPELLTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

public:
	void ApplyDamage(float Amount);

	bool IsDead() const { return CurrentHealth <= 0.f; }

	UPROPERTY(EditAnywhere, Category="Health")
	int32 XPOnDeath;

	FORCEINLINE int GetDeathXP() const { return XPOnDeath; }
protected:
	UPROPERTY(EditDefaultsOnly, Category="Health")
	float MaxHealth = 100.f;

	float CurrentHealth = MaxHealth;

	
};
