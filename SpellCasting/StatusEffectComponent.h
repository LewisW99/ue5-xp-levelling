// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellDataAsset.h"
#include "StatusEffectComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPELLTEST_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatusEffectComponent();
	
	void ApplyEffect(ESpellType SpellType, float Strength, float Duration);

protected:
	virtual void BeginPlay() override;

private:
	void ApplyFire(float Strength, float Duration);
	void ApplyIce(float Strength, float Duration);
	void ApplyLightning(float Strength);

	FTimerHandle FireTimer;
};
