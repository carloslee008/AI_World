// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ExplodingBarrel.generated.h"

UCLASS()
class AI_WORLD_API AExplodingBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplodingBarrel();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	UStaticMeshComponent* BarrelMesh;
	
	UPROPERTY(ReplicatedUsing=OnRep_HitPoints, VisibleAnywhere, Category="Barrel")
	float HitPoints;

	UFUNCTION()
	void OnRep_HitPoints();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	float DamageRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Barrel")
	USoundCue* ExplosionSound;

	UPROPERTY(EditAnywhere, Category="Barrel")
	UParticleSystemComponent* FireParticle;
	
	UPROPERTY(EditAnywhere, Category="Barrel")
	URadialForceComponent* RadialForce;

	UPROPERTY(EditAnywhere, Category="Barrel")
	UNiagaraSystem* ExplosionParticle;

	UPROPERTY()
	bool bDoOnce;

protected:

	void OnDamageTaken(AActor* DamagedActor, float DamageTaken, UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:

	FORCEINLINE float GetHealth() const { return HitPoints; }
};
