// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"

#include "AI_World/AIWorldComponents/CombatComponent.h"
#include "AI_World/Character/Collector.h"


void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ACollector* Collector = Cast<ACollector>(OtherActor);
	if (Collector)
	{
		UCombatComponent* Combat = Collector->GetCombat();
		if (Combat)
		{
			Combat->PickupAmmo(WeaponType, AmmoAmount);
		}
	}
	Destroy();
}
