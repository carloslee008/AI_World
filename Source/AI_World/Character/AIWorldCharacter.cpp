// Fill out your copyright notice in the Description page of Project Settings.

//
//
// #include "AIWorldCharacter.h"
// #include "Camera/CameraComponent.h"
// #include "GameFramework/SpringArmComponent.h"
// #include "Components/InputComponent.h"
// #include "EnhancedInputSubsystems.h"
// #include "EnhancedInputComponent.h"
// #include "AI_World/AIWorldComponents/CombatComponent.h"
// #include "AI_World/Weapon/Weapon.h"
// #include "Components/CapsuleComponent.h"
// #include "Components/WidgetComponent.h"
// #include "GameFramework/CharacterMovementComponent.h"
// #include "Kismet/KismetMathLibrary.h"
// #include "Net/UnrealNetwork.h"
// #include "HumanoidAnimInstance.h"
// #include "AI_World/AI_World.h"
// #include "AI_World/GameMode/AIWorldGameMode.h"
// #include "AI_World/PlayerController/AIWorldPlayerController.h"
// #include "TimerManager.h"
// #include "AI_World/PlayerState/AIWorldPlayerState.h"
// #include "AI_World/Weapon/WeaponTypes.h"
// #include "Kismet/GameplayStatics.h"
//
// // Sets default values
// AAIWorldCharacter::AAIWorldCharacter()
// {
//  	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = true;
//
// 	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
// 	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
// 	CameraBoom->SetupAttachment(GetMesh());
// 	CameraBoom->TargetArmLength = 600.0f;
// 	CameraBoom->bUsePawnControlRotation = true;
// 	
// 	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
// 	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
// 	FollowCamera->bUsePawnControlRotation = false;
//
// 	bUseControllerRotationYaw = false;
// 	GetCharacterMovement()->bOrientRotationToMovement = true;
//
// 	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
// 	OverheadWidget->SetupAttachment(RootComponent);
//
// 	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
// 	Combat->SetIsReplicated(true);
//
// 	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
// 	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
// 	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);
// 	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
// 	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
// 	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
// 	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 850.f);
//
// 	TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 	NetUpdateFrequency = 66.f;
// 	MinNetUpdateFrequency = 33.f;
// }
//
// void AAIWorldCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
// 	DOREPLIFETIME_CONDITION(AAIWorldCharacter, OverlappingWeapon, COND_OwnerOnly);
// 	DOREPLIFETIME(AAIWorldCharacter, Health);
// 	DOREPLIFETIME(AAIWorldCharacter, bDisableGameplay);
// }
//
// void AAIWorldCharacter::OnRep_ReplicatedMovement()
// {
// 	Super::OnRep_ReplicatedMovement();
// 	SimProxiesTurn();
// 	TimeSinceLastMovementReplication = 0.f;
// }
//
// void AAIWorldCharacter::Down()
// {
// 	if (Combat && Combat->EquippedWeapon)
// 	{
// 		Combat->EquippedWeapon->Dropped();
// 	}
// 	MulticastDown();
// 	GetWorldTimerManager().SetTimer(
// 		DownedTimer,
// 		this,
// 		&AAIWorldCharacter::DownedTimerFinished,
// 		DownedDelay);
// }
//
// void AAIWorldCharacter::DownedTimerFinished()
// {
// 	AAIWorldGameMode* AIWorldGameMode = GetWorld()->GetAuthGameMode<AAIWorldGameMode>();
// 	if (AIWorldGameMode)
// 	{
// 		AIWorldGameMode->RequestRevive(this, Controller);
// 	}
// }
//
// void AAIWorldCharacter::MulticastDown_Implementation()
// {
// 	if (AIWorldPlayerController)
// 	{
// 		AIWorldPlayerController->SetHUDWeaponAmmo(0);
// 	}
// 	bDowned = true;
// 	PlayDownedMontage();
// 	
// 	//Disable Character Movement
// 	GetCharacterMovement()->DisableMovement();
// 	GetCharacterMovement()->StopMovementImmediately();
// 	if (Combat)
// 	{
// 		Combat->FireButtonPressed(false);
// 	}
// 	if (AIWorldPlayerController)
// 	{
// 		DisableInput(AIWorldPlayerController);
// 	}
// 	// Disable Collision
// 	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// }
//
// void AAIWorldCharacter::Destroyed()
// {
// 	Super::Destroyed();
//
// 	AAIWorldGameMode* AIWorldGameMode = Cast<AAIWorldGameMode>(UGameplayStatics::GetGameMode(this));
// 	bool bMatchNotInProgress = AIWorldGameMode && AIWorldGameMode->GetMatchState() != MatchState::InProgress;
// 	if (Combat && Combat->EquippedWeapon && bMatchNotInProgress)
// 	{
// 		Combat->EquippedWeapon->Destroy();
// 	}
// }
//
// // Called when the game starts or when spawned
// void AAIWorldCharacter::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
// 	{
// 		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
// 		if (DefaultMappingContext)
// 		{
// 			Subsystem->AddMappingContext(DefaultMappingContext, 0);
// 		}
// 	}
//
// 	UpdateHUDHealth();
// 	if (HasAuthority())
// 	{
// 		OnTakeAnyDamage.AddDynamic(this, &AAIWorldCharacter::ReceiveDamage);
// 	}
//
// 	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
// 	{
// 		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
// 		{
// 			Subsystem->AddMappingContext(DefaultMappingContext, 0);
// 		}
// 	}
// }
//
//
// void AAIWorldCharacter::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// 	RotateInPlace(DeltaTime);
// 	HideCameraIfCharacterClose();
// 	PollInit();
// }
//
// void AAIWorldCharacter::RotateInPlace(float DeltaTime)
// {
// 	if (bDisableGameplay)
// 	{
// 		bUseControllerRotationYaw = false;
// 		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 		return;
// 	}
// 	if (GetLocalRole() > ROLE_SimulatedProxy && IsLocallyControlled())
// 	{
// 		AimOffset(DeltaTime);
// 	}
// 	else
// 	{
// 		TimeSinceLastMovementReplication += DeltaTime;
// 		if (TimeSinceLastMovementReplication > 0.25f)
// 		{
// 			OnRep_ReplicatedMovement();
// 		}
// 		CalculateAO_Pitch();
// 	}
// }
//
// // Called to bind functionality to input
// void AAIWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	// Super::SetupPlayerInputComponent(PlayerInputComponent);
//
// 	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
// 	{
// 		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::Move);
// 		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::Look);
// 		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::Jump);
// 		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAIWorldCharacter::StopJumping);
// 		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::Interact);
// 		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::CrouchButtonPressed);
// 		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::AimButtonPressed);
// 		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AAIWorldCharacter::FireButtonPressed);
// 		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AAIWorldCharacter::FireButtonReleased);
// 		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AAIWorldCharacter::ReloadButtonPressed);
// 	}
// }
//
// void AAIWorldCharacter::Move(const FInputActionValue& Value)
// {
// 	if (bDisableGameplay) return;
// 	const FVector2d MovementVector = Value.Get<FVector2d>();
// 	if (IsValid(Controller))
// 	{
// 		const FRotator Rotation = Controller->GetControlRotation();
// 		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
// 		
// 		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 		
// 		AddMovementInput(ForwardDirection, MovementVector.Y);
// 		AddMovementInput(RightDirection, MovementVector.X);
// 	}
// 	
// }
//
// void AAIWorldCharacter::Look(const FInputActionValue& Value)
// {
// 	const FVector2d LookAxisValue = Value.Get<FVector2d>();
// 	
// 	if (GetController())
// 	{
// 		AddControllerYawInput(LookAxisValue.X);
// 		AddControllerPitchInput(LookAxisValue.Y);
// 	}
// }
//
// void AAIWorldCharacter::Interact(const FInputActionValue& Value)
// {
// 	if (bDisableGameplay) return;
// 	if (Combat)
// 	{
// 		if (HasAuthority())
// 		{
// 			Combat->EquipWeapon(OverlappingWeapon);
// 		}
// 		else
// 		{
// 			ServerInteract();
// 		}
// 	}
// }
//
// void AAIWorldCharacter::ServerInteract_Implementation()
// {
// 	if (Combat)
// 	{
// 		Combat->EquipWeapon(OverlappingWeapon);
// 	}
// }
//
// void AAIWorldCharacter::CrouchButtonPressed(const FInputActionValue& Value)
// {
// 	if (bDisableGameplay) return;
// 	if (bIsCrouched)
// 	{
// 		UnCrouch();
// 	}
// 	else
// 	{
// 		Crouch();
// 	}
// }
//
// void AAIWorldCharacter::AimButtonPressed(const FInputActionValue& Value)
// {
// 	if (Combat)
// 	{
// 		Combat->SetAiming(Value.Get<bool>());
// 	}
// }
//
// void AAIWorldCharacter::CalculateAO_Pitch()
// {
// 	AO_Pitch = GetBaseAimRotation().Pitch;
// 	if (AO_Pitch > 90.f && !IsLocallyControlled())
// 	{
// 		// Map pitch from [270, 360) to [-90.0)
// 		FVector2d InRange(270.f, 360.f);
// 		FVector2d OutRange(-90.f, 0.f);
// 		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
// 	}
// }
//
// float AAIWorldCharacter::CalculateSpeed()
// {
// 	FVector Velocity = GetVelocity();
// 	Velocity.Z = 0.f;
// 	return Velocity.Size();
// }
//
// void AAIWorldCharacter::AimOffset(float DeltaTime)
// {
// 	if (Combat && Combat->EquippedWeapon == nullptr) return; // no weapon
// 	float Speed = CalculateSpeed();
// 	bool bIsInAir = GetCharacterMovement()->IsFalling();
// 	
// 	if (Speed == 0.f && !bIsInAir)  // standing still, not jumping
// 	{
// 		bRotateRootBone = true;
// 		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
// 		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
// 		AO_Yaw = DeltaAimRotation.Yaw;
// 		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
// 		{
// 			InterpAO_Yaw = AO_Yaw;
// 		}
// 		bUseControllerRotationYaw = true;
// 		TurnInPlace(DeltaTime);
// 	}
// 	if (Speed > 0.f || bIsInAir) // running or jumping
// 	{
// 		bRotateRootBone = false;
// 		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
// 		AO_Yaw = 0.f;
// 		bUseControllerRotationYaw = true;
// 		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 	}
//
// 	CalculateAO_Pitch();
// }
//
// void AAIWorldCharacter::SimProxiesTurn()
// {
// 	if (Combat == nullptr || Combat->EquippedWeapon == nullptr ) return;
// 	bRotateRootBone = false;
// 	float Speed = CalculateSpeed();
// 	if (Speed > 0.f)
// 	{
// 		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 		return;
// 	}
// 	
// 	ProxyRotationLastFrame = ProxyRotation;
// 	ProxyRotation = GetActorRotation();
// 	ProxyYaw = UKismetMathLibrary::NormalizedDeltaRotator(ProxyRotation, ProxyRotationLastFrame).Yaw;
// 	
// 	if (FMath::Abs(ProxyYaw) > TurnThreshold)
// 	{
// 		if (ProxyYaw > TurnThreshold)
// 		{
// 			TurningInPlace = ETurningInPlace::ETIP_Right;
// 		}
// 		else if (ProxyYaw < TurnThreshold)
// 		{
// 			TurningInPlace = ETurningInPlace::ETIP_Left;
// 		}
// 		else
// 		{
// 			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 		}
// 		return;
// 	}
// 	TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// }
//
// void AAIWorldCharacter::FireButtonPressed(const FInputActionValue& Value)
// {
// 	if (bDisableGameplay) return;
// 	if (Combat)
// 	{
// 		Combat->FireButtonPressed(true);
// 	}
// }
//
// void AAIWorldCharacter::FireButtonReleased(const FInputActionValue& Value)
// {
// 	if (bDisableGameplay) return;
// 	if (Combat)
// 	{
// 		Combat->FireButtonPressed(false);
// 	}
// }
//
// void AAIWorldCharacter::ReloadButtonPressed(const FInputActionValue& Value)
// {
// 	if (Combat)
// 	{
// 		Combat->Reload();
// 	}
// }
//
// void AAIWorldCharacter::TurnInPlace(float DeltaTime)
// {
// 	if (AO_Yaw > 90.f)
// 	{
// 		TurningInPlace = ETurningInPlace::ETIP_Right;
// 	}
// 	else if (AO_Yaw < -90.f)
// 	{
// 		TurningInPlace = ETurningInPlace::ETIP_Left;
// 	}
// 	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
// 	{
// 		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 8.f);
// 		AO_Yaw = InterpAO_Yaw;
// 		if (FMath::Abs(AO_Yaw) < 15.f)
// 		{
// 			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
// 		}
// 	}
// }
//
// void AAIWorldCharacter::HideCameraIfCharacterClose()
// {
// 	if (!IsLocallyControlled()) return;
// 	
// 	if ((FollowCamera->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold)
// 	{
// 		GetMesh()->SetVisibility(false);
// 		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
// 		{
// 			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = true;
// 		}
// 	}
// 	else
// 	{
// 		GetMesh()->SetVisibility(true);
// 		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
// 		{
// 			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = false;
// 		}
// 	}
// }
//
// void AAIWorldCharacter::OnRep_Health()
// {
// 	UpdateHUDHealth();
// 	PlayHitReactMontage();
// }
//
// void AAIWorldCharacter::UpdateHUDHealth()
// {
// 	AIWorldPlayerController = AIWorldPlayerController == nullptr ? Cast<AAIWorldPlayerController>(Controller) : AIWorldPlayerController;
// 	if (AIWorldPlayerController)
// 	{
// 		AIWorldPlayerController->SetHUDHealth(Health, MaxHealth);
// 	}
// }
//
// void AAIWorldCharacter::PollInit()
// {
// 	if (AIWorldPlayerState == nullptr)
// 	{
// 		AIWorldPlayerState = GetPlayerState<AAIWorldPlayerState>();
// 		if (AIWorldPlayerState)
// 		{
// 			AIWorldPlayerState->AddToScore(0.f);
// 			AIWorldPlayerState->AddToDeaths(0);
// 		}
// 	}
// }
//
// void AAIWorldCharacter::SetOverlappingWeapon(AWeapon* Weapon)
// {
// 	if (IsLocallyControlled())
// 	{
// 		if (OverlappingWeapon)
// 		{
// 			OverlappingWeapon->ShowPickupWidget(false);
// 		}
// 	}
// 	OverlappingWeapon = Weapon;
// 	if (IsLocallyControlled())
// 	{
// 		if (OverlappingWeapon)
// 		{
// 			OverlappingWeapon->ShowPickupWidget(true);
// 		}
// 	}
// }
//
// void AAIWorldCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon)
// {
// 	if (OverlappingWeapon)
// 	{
// 		OverlappingWeapon->ShowPickupWidget(true);
// 	}
// 	if (LastWeapon)
// 	{
// 		LastWeapon->ShowPickupWidget(false);
// 	}
// }
//
// bool AAIWorldCharacter::IsWeaponEquipped()
// {
// 	return (Combat && Combat->EquippedWeapon);
// }
//
// bool AAIWorldCharacter::IsAiming()
// {
// 	return (Combat && Combat->bAiming);
// }
//
// AWeapon* AAIWorldCharacter::GetEquippedWeapon()
// {
// 	if (Combat == nullptr) return nullptr;
// 	return Combat->EquippedWeapon;
// }
//
// FVector AAIWorldCharacter::GetHitTarget() const
// {
// 	if (Combat == nullptr) return FVector();
// 	return Combat->HitTarget;
// }
//
// void AAIWorldCharacter::PostInitializeComponents()
// {
// 	Super::PostInitializeComponents();
// 	if (Combat)
// 	{
// 		Combat->Character = this;
// 	}
// }
//
// void AAIWorldCharacter::PlayFireMontage(bool bAiming)
// {
// 	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;
//
// 	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
// 	if (AnimInstance && FireWeaponMontage)
// 	{
// 		AnimInstance->Montage_Play(FireWeaponMontage);
// 		FName SectionName;
// 		SectionName = bAiming ? FName("RifleAim") : FName("RifleHip");
// 		AnimInstance->Montage_JumpToSection(SectionName);
// 	}
// }
//
// void AAIWorldCharacter::PlayDownedMontage()
// {
// 	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
// 	if (AnimInstance && DownedMontage)
// 	{
// 		AnimInstance->Montage_Play(DownedMontage);
// 	}
// }
//
// void AAIWorldCharacter::PlayHitReactMontage()
// {
// 	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;
//
// 	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
// 	if (AnimInstance && HitReactMontage)
// 	{
// 		AnimInstance->Montage_Play(HitReactMontage);
// 		FName SectionName("FromFront");
// 		AnimInstance->Montage_JumpToSection(SectionName);
// 	}
// }
//
// void AAIWorldCharacter::PlayReloadMontage()
// {
// 	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;
//
// 	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
// 	if (AnimInstance && ReloadMontage)
// 	{
// 		AnimInstance->Montage_Play(ReloadMontage);
// 		FName SectionName;
//
// 		switch (Combat->EquippedWeapon->GetWeaponType())
// 		{
// 		case EWeaponType::EWT_AssaultRifle:
// 			SectionName = FName("Rifle");
// 			break;
// 		case EWeaponType::EWT_RocketLauncher:
// 			SectionName = FName("Rifle");
// 			break;
// 		}
// 		AnimInstance->Montage_JumpToSection(SectionName);
// 	}
// }
//
// void AAIWorldCharacter::ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
// 	AController* InstigatorController, AActor* DamageCauser)
// {
// 	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
// 	UpdateHUDHealth();
// 	PlayHitReactMontage();
//
// 	if (Health == 0.f)
// 	{
// 		AAIWorldGameMode* AIWorldGameMode = GetWorld()->GetAuthGameMode<AAIWorldGameMode>();
// 		if  (AIWorldGameMode)
// 		{
// 			AIWorldPlayerController = AIWorldPlayerController == nullptr ? Cast<AAIWorldPlayerController>(Controller) : AIWorldPlayerController;
// 			AAIWorldPlayerController* AttackerController = Cast<AAIWorldPlayerController>(InstigatorController);
// 			AIWorldGameMode->PlayerEliminated(this, AIWorldPlayerController, AttackerController);
// 		}
// 	}
// }
//
// void AAIWorldCharacter::Jump()
// {
// 	if (bDisableGameplay) return;
// 	if (bIsCrouched)
// 	{
// 		UnCrouch();
// 	}
// 	else
// 	{
// 		Super::Jump();
// 	}
// }
//
// ECombatState AAIWorldCharacter::GetCombatState() const
// {
// 	if (Combat == nullptr) return ECombatState::ECS_MAX;
// 	return Combat->CombatState;
// }
