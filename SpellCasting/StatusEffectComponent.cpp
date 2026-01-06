// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "Health/HealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusEffectComponent::ApplyEffect(
	ESpellType SpellType,
	float Strength,
	float Duration)
{
	switch (SpellType)
	{
	case ESpellType::Fire:
		ApplyFire(Strength, Duration);
		break;

	case ESpellType::Ice:
		ApplyIce(Strength, Duration);
		break;

	case ESpellType::Lightning:
		ApplyLightning(Strength);
		break;

	default:
		break;
	}
}

void UStatusEffectComponent::ApplyFire(float Strength, float Duration)
{
	if (UHealthComponent* Health =
		GetOwner()->FindComponentByClass<UHealthComponent>())
	{
		const float TickDamage = 5.f * Strength;
		const float TickRate = 1.f;

		int32 Ticks = FMath::CeilToInt(Duration / TickRate);

		GetWorld()->GetTimerManager().SetTimer(
			FireTimer,
			[Health, TickDamage, Ticks]() mutable
			{
				if (!Health || Health->IsDead()) return;
				Health->ApplyDamage(TickDamage);
				--Ticks;
			},
			TickRate,
			true
		);
	}
}

void UStatusEffectComponent::ApplyIce(float Strength, float Duration)
{
	if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
	{
		if (UCharacterMovementComponent* Move = Char->GetCharacterMovement())
		{
			const float OriginalSpeed = Move->MaxWalkSpeed;
			Move->MaxWalkSpeed *= FMath::Clamp(1.f - Strength, 0.2f, 1.f);

			FTimerHandle ResetTimer;
			GetWorld()->GetTimerManager().SetTimer(
				ResetTimer,
				[Move, OriginalSpeed]()
				{
					Move->MaxWalkSpeed = OriginalSpeed;
				},
				Duration,
				false
			);
		}
	}
}

void UStatusEffectComponent::ApplyLightning(float Strength)
{
	if (UHealthComponent* Health =
		GetOwner()->FindComponentByClass<UHealthComponent>())
	{
		Health->ApplyDamage(15.f * Strength);
	}
}