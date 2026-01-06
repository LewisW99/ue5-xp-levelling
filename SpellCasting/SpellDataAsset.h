// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FSpellStats
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float ManaCost = 15.f;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed = 2000.f;

	UPROPERTY(EditDefaultsOnly)
	float EffectStrength = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float EffectDuration = 3.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpellProjectile> ProjectileClass;
};

UENUM(BlueprintType)
enum class ESpellType : uint8
{
	Fire        UMETA(DisplayName="Fire"),
	Ice         UMETA(DisplayName="Ice"),
	Lightning   UMETA(DisplayName="Lightning"),
	Light       UMETA(DisplayName="Light")
};
/**
 * 
 */
UCLASS()
class SPELLTEST_API USpellDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	ESpellType SpellType;

	UPROPERTY(EditDefaultsOnly)
	FSpellStats Stats;
};
