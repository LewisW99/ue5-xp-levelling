// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDataAsset.h"
#include "GameFramework/Actor.h"
#include "SpellProjectile.generated.h"

UCLASS()
class SPELLTEST_API ASpellProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpellProjectile();

	void Init(const FSpellStats& InStats);

	
protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* Movement;

	float Damage = 0.f;

private:
	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	ESpellType SpellType;
	float EffectStrength;
	float EffectDuration;

	UPROPERTY(VisibleAnywhere, Category="CharacterRef")
	class ASpellTestCharacter* SpellCharacter; 
};
