// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellCastingComponent.generated.h"


class USpellDataAsset;
class UManaComponent;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPELLTEST_API USpellCastingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpellCastingComponent();

	void CycleSpell(int32 Direction);
	void CastSpell();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Spells")
	TArray<USpellDataAsset*> SpellList;
	UPROPERTY()
	UManaComponent* Mana;
	int32 CurrentSpellIndex = 0;

	float LastCastTime = -100.f;

	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
