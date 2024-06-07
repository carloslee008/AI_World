// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanoidAnimInstance.h"
#include "Collector.h"
#include "AI_World/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI_World/AI_WorldTypes/CombatState.h"

void UHumanoidAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Collector = Cast<ACollector>(TryGetPawnOwner());
}

void UHumanoidAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Collector == nullptr)
	{
		Collector = Cast<ACollector>(TryGetPawnOwner());
	}
	if (Collector == nullptr) return;

	FVector Velocity = Collector->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = Collector->GetCharacterMovement()->IsFalling();
	bIsAccelerating = Collector->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = Collector->IsWeaponEquipped();
	EquippedWeapon = Collector->GetEquippedWeapon();
	bIsCrouched = Collector->bIsCrouched;
	bAiming = Collector->IsAiming();
	TurningInPlace = Collector->GetTurningInPlace();
	bRotateRootBone = Collector->ShouldRotateRootBone();
	bDowned = Collector->IsDowned();

	//Offset Yaw for Strafing
	FRotator AimRotation = Collector->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Collector->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = Collector->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = Collector->GetAOYaw();
	AO_Pitch = Collector->GetAOPitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && Collector->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		Collector->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		if (Collector->IsLocallyControlled())
		{
			// bLocallyControlled = true;
			// FTransform RightHandTransform = Collector->GetMesh()->GetSocketTransform(FName("r-hand"), RTS_World);
			// FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), Collector->GetHitTarget());
			// RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 30.f);

			bLocallyControlled = true;
			FTransform RightHandTransform = Collector->GetMesh()->GetSocketTransform(FName("hand_r"), RTS_World);
			RightHandRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - Collector->GetHitTarget()));
			
			// FTransform MuzzleTipTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash"), RTS_World);
			// FVector MuzzleX(FRotationMatrix(MuzzleTipTransform.GetRotation().Rotator()).GetUnitAxis(EAxis::X));
			// DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), MuzzleTipTransform.GetLocation() + MuzzleX * 1000.f, FColor::Red);
			// DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), Collector->GetHitTarget(), FColor::Orange);
		}
		
	}

	bUseFABRIK = Collector->GetCombatState() == ECombatState::ECS_Unoccupied;
	bUseAimOffsets = Collector->GetCombatState() == ECombatState::ECS_Unoccupied && !Collector->GetDisplayGameplay();
	bTransformRightHand = Collector->GetCombatState() == ECombatState::ECS_Unoccupied && !Collector->GetDisplayGameplay();
}
