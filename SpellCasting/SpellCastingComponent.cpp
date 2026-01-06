// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCastingComponent.h"

#include "ManaComponent.h"
#include "SpellDataAsset.h"
#include "SpellProjectile.h"


// Sets default values for this component's properties
USpellCastingComponent::USpellCastingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USpellCastingComponent::CycleSpell(int32 Direction)
{
	if (SpellList.Num() == 0) return;

	CurrentSpellIndex =
		(CurrentSpellIndex + Direction + SpellList.Num()) % SpellList.Num();
}


// Called when the game starts
void USpellCastingComponent::BeginPlay()
{
	Super::BeginPlay();

	Mana = GetOwner()->FindComponentByClass<UManaComponent>();
	ensureMsgf(Mana, TEXT("SpellCastingComponent Requires Mana"));
	
}


// Called every frame
void USpellCastingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellCastingComponent::CastSpell()
{
	if (!SpellList.IsValidIndex(CurrentSpellIndex)) return;

	const USpellDataAsset* Spell = SpellList[CurrentSpellIndex];
	const FSpellStats& Stats = Spell->Stats;

	const float Time = GetWorld()->GetTimeSeconds();
	if (Time - LastCastTime < Stats.Cooldown) return;
	if (!Mana->Consume(Stats.ManaCost)) return;

	LastCastTime = Time;

	AActor* Owner = GetOwner();
	if (!Owner) return;

	AController* Controller = Owner->GetInstigatorController();
	if (!Controller) return;

	
	const FRotator ControlRot = Controller->GetControlRotation();
	const FVector Forward = ControlRot.Vector();

	// Simple forward muzzle (works for now)
	const FVector Muzzle =
		Owner->GetActorLocation() +
		Forward * 100.f +
		FVector(0.f, 0.f, 50.f); // chest height

	FActorSpawnParameters Params;
	Params.Owner = Owner;
	Params.Instigator = Cast<APawn>(Owner);
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASpellProjectile* Projectile =
		GetWorld()->SpawnActor<ASpellProjectile>(
			Stats.ProjectileClass,
			Muzzle,
			ControlRot,
			Params
		);

	if (Projectile)
	{
		Projectile->Init(Stats);
	}

	UE_LOG(LogTemp, Log, TEXT("Casting %s (Mana %.1f)"),
		*UEnum::GetValueAsString(Spell->SpellType),
		Mana->GetMana());
}
