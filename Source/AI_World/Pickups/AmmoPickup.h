// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AI_World/Weapon/WeaponTypes.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class AI_WORLD_API AAmmoPickup : public APickup
{
	GENERATED_BODY()

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult)
	override;
private:
	int32 AmmoAmount = 5;

	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;
};