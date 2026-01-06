// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellProjectile.h"

#include "SpellTestCharacter.h"
#include "StatusEffectComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Health/HealthComponent.h"
#include "XPSystem/XPComponent.h"


ASpellProjectile::ASpellProjectile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Mesh->SetGenerateOverlapEvents(true);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->UpdatedComponent = Mesh;   
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = 2000.f;
	Movement->MaxSpeed = 1000000.f;

	SetLifeSpan(3.5f);
}

void ASpellProjectile::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			SpellCharacter = Cast<ASpellTestCharacter>(PC->GetPawn());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PC IS NUll"));
		}
	}
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpellProjectile::OnOverlap);
}

void ASpellProjectile::Init(const FSpellStats& InStats)
{
	Damage = InStats.Damage;
	EffectStrength = InStats.EffectStrength;
	EffectDuration = InStats.EffectDuration;
	
	Movement->InitialSpeed = InStats.ProjectileSpeed;
	Movement->MaxSpeed = InStats.ProjectileSpeed;

	Movement->Velocity = GetActorForwardVector() * InStats.ProjectileSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Projectile speed: %f"),
	Movement->Velocity.Size());
}

void ASpellProjectile::OnOverlap(
	UPrimitiveComponent*,
	AActor* OtherActor,
	UPrimitiveComponent*,
	int32,
	bool,
	const FHitResult&)
{
	if (!OtherActor || OtherActor == GetOwner())
		return;

	if (UHealthComponent* Health =
		OtherActor->FindComponentByClass<UHealthComponent>())
	{
		Health->ApplyDamage(Damage);
		if (Health->IsDead())
		{
			if (UXPComponent* XPComponent = SpellCharacter->GetXPComponent())
			{
				XPComponent->AddXP(Health->GetDeathXP());
				UE_LOG(LogTemp,Warning, TEXT("XP Awarded: %i"), Health->GetDeathXP());
			}
			OtherActor->Destroy();
			
		}
	}
	
	if (UStatusEffectComponent* Effects =
		OtherActor->FindComponentByClass<UStatusEffectComponent>())
	{
		Effects->ApplyEffect(SpellType, EffectStrength, EffectDuration);
	}
	
	Destroy();
}



