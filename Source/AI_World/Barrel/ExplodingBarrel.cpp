// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingBarrel.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AExplodingBarrel::AExplodingBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	RootComponent = BarrelMesh;

	FireParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particle"));
	FireParticle->SetupAttachment(BarrelMesh);
	FireParticle->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));
	RadialForce->SetupAttachment(BarrelMesh);
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;
	RadialForce->bIgnoreOwningActor = false;

	HitPoints = 50.f;
	ExplosionDamage = 5.f;
	DamageRadius = 100.f;

}

void AExplodingBarrel::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExplodingBarrel, HitPoints);
}

// Called when the game starts or when spawned
void AExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplodingBarrel::OnRep_HitPoints()
{
	if (HitPoints <= 0)
	{
		Destroy();
	}
}

void AExplodingBarrel::OnDamageTaken(AActor* DamagedActor, const float DamageTaken, UDamageType* DamageType,
                                     AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageTaken > 0 && HitPoints > 0)
	{
		HitPoints -= DamageTaken;
		UE_LOG(LogTemp, Warning, TEXT("Damage taken, Barrel is on fire. Health = %f"), HitPoints);

		//Set barrel on fire
		if (!FireParticle->IsActive())
		{
			FireParticle->Activate();
		}

		//Start a countdown if not started.
	}

	//Explode when health is less than or equal to zero
	if (bDoOnce)
	{
		if (HitPoints <= 0)
		{
			//Deactivate fire
			if (FireParticle)
			{
				FireParticle->Deactivate();
			}

			// Save location to spawn all other events in that location.
			FVector BarrelLocation = GetActorLocation();

			//Apply Damage
			UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, BarrelLocation, DamageRadius, nullptr, TArray<AActor*>(), this);

			//Apply radial force
			if (RadialForce)
			{
				RadialForce->FireImpulse();
			}

			//Apply particles and sound
			if (ExplosionSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, BarrelLocation);
			}
			if (ExplosionParticle)
			{
				UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionParticle, BarrelMesh, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
			}
		}
	}
}


