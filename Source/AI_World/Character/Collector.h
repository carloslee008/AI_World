// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AI_World/AI_WorldTypes/TurningInPlace.h"
#include "AI_World/Interfaces/InteractWithCrosshairsInterface.h"
#include "AI_World/AI_WorldTypes/CombatState.h"
#include "AI_World/Interfaces/Interactables.h"
#include "Camera/CameraComponent.h"
#include "Collector.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class AI_WORLD_API ACollector : public ACharacter, public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()

public:
	ACollector();
	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bAiming);
	void PlayReloadMontage();
	void PlayDownedMontage();
	void PlayThrowGrenadeMontage();

	virtual void OnRep_ReplicatedMovement() override;

	void Down();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastDown();

	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateInPlace(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TogglePOVAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowGrenadeAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void CrouchButtonPressed(const FInputActionValue& Value);
	void AimButtonPressed(const FInputActionValue& Value);
	void CalculateAO_Pitch();
	void AimOffset(float DeltaTime);
	void SimProxiesTurn();
	void FireButtonPressed(const FInputActionValue& Value);
	void FireButtonReleased(const FInputActionValue& Value);
	void ReloadButtonPressed(const FInputActionValue& Value);
	void TogglePOV(const FInputActionValue& Value);
	void ThrowGrenadePressed(const FInputActionValue& Value);
	void PlayHitReactMontage();
	virtual void Jump() override;

	virtual void Destroyed() override;

	UFUNCTION()
	void ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);
	void UpdateHUDHealth();
	// Poll for any relevant classes and initialize our HUD
	void PollInit();

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* CharacterMesh;
	
	UPROPERTY(VisibleAnywhere, Category= Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category= Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category= Camera)
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing= OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* Combat;

	UFUNCTION(Server, Reliable)
	void ServerInteract();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	/**
	 * Animation Montages
	 */
	
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ReloadMontage;
	
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* DownedMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ThrowGrenadeMontage;
	
	void HideCameraIfCharacterClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;
	float CalculateSpeed();

	//Sprint
	UPROPERTY(EditAnywhere)
	float SprintSpeed = 600.f;
	float WalkSpeed = 250.f;

	/**
	 * Player Health
	 */

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 150.f;

	UPROPERTY(ReplicatedUsing= OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 150.f;

	UFUNCTION()
	void OnRep_Health();

	UPROPERTY()
	class AAIWorldPlayerController* AIWorldPlayerController;

	bool bDowned = false;

	FTimerHandle DownedTimer;

	UPROPERTY(EditDefaultsOnly)
	float DownedDelay = 3.f;

	void DownedTimerFinished();

	UPROPERTY()
	class AAIWorldPlayerState* AIWorldPlayerState;

	/**
	* Grenade
	*/

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachedGrenade;
	
public:	
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAOYaw() const { return AO_Yaw; }
	FORCEINLINE float GetAOPitch() const { return AO_Pitch; }

	/**
	 * Getter functions
	 */ 
	AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FVector GetHitTarget() const;
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsDowned() const { return bDowned; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	ECombatState GetCombatState() const;
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }
	FORCEINLINE bool GetDisplayGameplay() const { return bDisableGameplay; }
	FORCEINLINE UAnimMontage* GetReloadMontage() const { return ReloadMontage; }
	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }
};