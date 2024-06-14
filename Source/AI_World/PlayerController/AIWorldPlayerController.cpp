// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWorldPlayerController.h"

#include "AI_World/Character/Collector.h"
#include "AI_World/HUD/AIWorldHUD.h"
#include "AI_World/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AI_World/GameMode/AIWorldGameMode.h"
#include "AI_World/HUD/Announcement.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "AI_World/AIWorldComponents/CombatComponent.h"
#include "AI_World/GameState/AIWorldGameState.h"
#include "AI_World/PlayerState/AIWorldPlayerState.h"
#include "AI_World/HUD//SniperScope.h"

void AAIWorldPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	AIWorldHUD = Cast<AAIWorldHUD>(GetHUD());
	ServerCheckMatchState();
}

void AAIWorldPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAIWorldPlayerController, MatchState);
}

void AAIWorldPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
	CheckTimeSync(DeltaTime);
	PollInit();
}

void AAIWorldPlayerController::CheckTimeSync(float DeltaTime)
{
	TimeSyncRunningTime += DeltaTime;
	if (IsLocalController() && TimeSyncRunningTime > TimeSyncFrequency)
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
		TimeSyncRunningTime = 0.f;
	}
}

void AAIWorldPlayerController::ClientJoinMidGame_Implementation(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime)
{
	WarmupTime = Warmup;
	MatchTime = Match;
	CooldownTime = Cooldown;
	LevelStartingTime = StartingTime;
	MatchState = StateOfMatch;
	OnMatchStateSet(MatchState);
	if (AIWorldHUD && MatchState == MatchState::WaitingToStart)
	{
		AIWorldHUD->AddAnnouncement();
	}
}

void AAIWorldPlayerController::ServerCheckMatchState_Implementation()
{
	AAIWorldGameMode* GameMode = Cast<AAIWorldGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		WarmupTime = GameMode->WarmupTime;
		MatchTime = GameMode->MatchTime;
		CooldownTime = GameMode->CooldownTime;
		LevelStartingTime = GameMode->LevelStartingTime;
		MatchState = GameMode->GetMatchState();
		ClientJoinMidGame(MatchState, WarmupTime, MatchTime, CooldownTime, LevelStartingTime);
	}
}

void AAIWorldPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACollector* Collector = Cast<ACollector>(InPawn);
	if (Collector)
	{
		SetHUDHealth(Collector->GetHealth(), Collector->GetMaxHealth());
	}
}

void AAIWorldPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->HealthBar &&
		AIWorldHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		AIWorldHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		AIWorldHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDHealth = Health;
		HUDMaxHealth = MaxHealth;
	}
}

void AAIWorldPlayerController::SetHUDScore(float Score)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->ScoreAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		AIWorldHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDScore = Score;
	}
}

void AAIWorldPlayerController::SetHUDDeaths(int32 Deaths)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->DeathCount;
	if (bHUDValid)
	{
		FString DeathCountText = FString::Printf(TEXT("%d"), Deaths);
		AIWorldHUD->CharacterOverlay->DeathCount->SetText(FText::FromString(DeathCountText));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDDeaths = Deaths;
	}
}

void AAIWorldPlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->WeaponAmmoAmount;
	if (bHUDValid)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		AIWorldHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::FromString(AmmoText));
	}
}

void AAIWorldPlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->CarriedAmmoAmount;
	if (bHUDValid)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		AIWorldHUD->CharacterOverlay->CarriedAmmoAmount->SetText(FText::FromString(AmmoText));
	}
}

void AAIWorldPlayerController::SetHUDDeathScreen(FString KillerName)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay->DeathMessage &&
		AIWorldHUD->CharacterOverlay->KillerName;
	if (bHUDValid)
	{
		FString KillerNameText = KillerName;
		AIWorldHUD->CharacterOverlay->KillerName->SetText(FText::FromString(KillerName));
		AIWorldHUD->CharacterOverlay->KillerName->SetVisibility(ESlateVisibility::Visible);
		AIWorldHUD->CharacterOverlay->DeathMessage->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAIWorldPlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->MatchCountdownText;
	if (bHUDValid)
	{
		if (CountdownTime < 0.f)
		{
			AIWorldHUD->CharacterOverlay->MatchCountdownText->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;
		
		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		AIWorldHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
}

void AAIWorldPlayerController::SetHUDAnnouncementCountdown(float CountdownTime)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->Announcement &&
		AIWorldHUD->Announcement->WarmupTime;
	if (bHUDValid)
	{
		if (CountdownTime < 0.f)
		{
			AIWorldHUD->Announcement->WarmupTime->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;
		
		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		AIWorldHUD->Announcement->WarmupTime->SetText(FText::FromString(CountdownText));
	}
}

void AAIWorldPlayerController::SetHUDSniperScope(bool bIsAiming)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;

	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->SniperScope &&
		AIWorldHUD->SniperScope->ScopeZoomIn;

	if (!AIWorldHUD->SniperScope)
	{
		AIWorldHUD->AddSniperScope();
	}

	if (bHUDValid)
	{
		if (bIsAiming)
		{
			AIWorldHUD->SniperScope->PlayAnimation(AIWorldHUD->SniperScope->ScopeZoomIn);
		}
		else
		{
			AIWorldHUD->SniperScope->PlayAnimation(AIWorldHUD->SniperScope->ScopeZoomIn,
				0.f,
				1,
				EUMGSequencePlayMode::Reverse
			);
		}
	}
}

void AAIWorldPlayerController::SetHUDGrenade(int32 Grenades)
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	bool bHUDValid = AIWorldHUD &&
		AIWorldHUD->CharacterOverlay &&
		AIWorldHUD->CharacterOverlay->GrenadeText;

	if (bHUDValid)
	{
		FString GrenadeText = FString::Printf(TEXT("%d"), Grenades);
		AIWorldHUD->CharacterOverlay->GrenadeText->SetText(FText::FromString(GrenadeText));
	}

	else
	{
		HUDGrenades = Grenades;
	}
	
}

void AAIWorldPlayerController::SetHUDTime()
{
	float TimeLeft = 0.f;
	if (MatchState == MatchState::WaitingToStart) TimeLeft = WarmupTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) TimeLeft = WarmupTime + MatchTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::Cooldown) TimeLeft = CooldownTime + WarmupTime + MatchTime - GetServerTime() + LevelStartingTime;
	uint32 SecondsLeft = FMath::CeilToInt(TimeLeft);

	if (HasAuthority())
	{
		AIWorldGameMode = AIWorldGameMode == nullptr ? Cast<AAIWorldGameMode>(UGameplayStatics::GetGameMode(this)) : AIWorldGameMode;
		if (AIWorldGameMode)
		{
			SecondsLeft = FMath::CeilToInt(AIWorldGameMode->GetCountdownTime() + LevelStartingTime);
		}
	}

	if (CountdownInt != SecondsLeft)
	{
		if (MatchState == MatchState::WaitingToStart || MatchState == MatchState::Cooldown)
		{
			SetHUDAnnouncementCountdown(TimeLeft);
		}
		if (MatchState == MatchState::InProgress)
		{
			SetHUDMatchCountdown(TimeLeft);
		}
	}
	
	CountdownInt = SecondsLeft;
}

void AAIWorldPlayerController::PollInit()
{
	if (CharacterOverlay == nullptr)
	{
		if (AIWorldHUD && AIWorldHUD->CharacterOverlay)
		{
			CharacterOverlay = AIWorldHUD->CharacterOverlay;
			if (CharacterOverlay)
			{
				SetHUDHealth(HUDHealth, HUDMaxHealth);
				SetHUDScore(HUDScore);
				SetHUDDeaths(HUDDeaths);
				SetHUDGrenade(HUDGrenades);

				ACollector* Collector = Cast<ACollector>(GetPawn());
				if (Collector && Collector->GetCombat())
				{
					SetHUDGrenade(Collector->GetCombat()->GetGrenades());
				}
			}
		}
	}
}

void AAIWorldPlayerController::ClientReportServerTime_Implementation(float TimeOfClientRequest,
                                                                     float TimeServerReceivedClientRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfClientRequest;
	float CurrentServerTime = TimeServerReceivedClientRequest + (0.5f * RoundTripTime);
	ClientServerDelta = CurrentServerTime - GetWorld()->GetTimeSeconds();
}

void AAIWorldPlayerController::ServerRequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();
	ClientReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}

float AAIWorldPlayerController::GetServerTime()
{
	if (HasAuthority()) return GetWorld()->GetTimeSeconds();
	else return GetWorld()->GetTimeSeconds() + ClientServerDelta;
}

void AAIWorldPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (IsLocalController())
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
	}
}

void AAIWorldPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;

	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
	else if (MatchState == MatchState::Cooldown)
	{
		HandleCooldown();
	}
}

void AAIWorldPlayerController::OnRep_MatchState()
{
	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
	else if (MatchState == MatchState::Cooldown)
	{
		HandleCooldown();
	}
}

void AAIWorldPlayerController::HandleMatchHasStarted()
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	if (AIWorldHUD)
	{
		if (AIWorldHUD->CharacterOverlay == nullptr) AIWorldHUD->AddCharacterOverlay();
		if (AIWorldHUD->Announcement)
		{
			AIWorldHUD->Announcement->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AAIWorldPlayerController::HandleCooldown()
{
	AIWorldHUD = AIWorldHUD == nullptr ? Cast<AAIWorldHUD>(GetHUD()) : AIWorldHUD;
	if (AIWorldHUD)
	{
		AIWorldHUD->CharacterOverlay->RemoveFromParent();
		bool bHUDValid = AIWorldHUD->Announcement &&
			AIWorldHUD->Announcement->AnnouncementText &&
			AIWorldHUD->Announcement->InfoText;
		
		if (bHUDValid)
		{
			AIWorldHUD->Announcement->SetVisibility(ESlateVisibility::Visible);
			FString AnnouncementText("New Match Starts In:");
			AIWorldHUD->Announcement->AnnouncementText->SetText(FText::FromString(AnnouncementText));

			AAIWorldGameState* AIWorldGameState = Cast<AAIWorldGameState>(UGameplayStatics::GetGameState(this));
			AAIWorldPlayerState* AIWorldPlayerState = GetPlayerState<AAIWorldPlayerState>();
			if (AIWorldGameState && AIWorldPlayerState)
			{
				TArray<AAIWorldPlayerState*> TopPlayers = AIWorldGameState->TopScoringPlayers;
				FString InfoTextString;
				if (TopPlayers.Num() == 0)
				{
					InfoTextString = FString("There is no winner.");
				}
				else if (TopPlayers.Num() == 1 && TopPlayers[0] == AIWorldPlayerState)
				{
					InfoTextString = FString("You are the winner!");
				}
				else if (TopPlayers.Num() == 1)
				{
					InfoTextString = FString::Printf(TEXT("Winner: \n%s"), *TopPlayers[0]->GetPlayerName());
				}
				else if (TopPlayers.Num() > 1)
				{
					InfoTextString = FString("Players tied for the win:\n");
					for (auto TiedPlayer : TopPlayers)
					{
						InfoTextString.Append(FString::Printf(TEXT("%s\n"), *TiedPlayer->GetPlayerName()));
					}
				}
				AIWorldHUD->Announcement->InfoText->SetText(FText::FromString(InfoTextString));
			}
		}
	}
	ACollector* Collector = Cast<ACollector>(GetPawn());
	if (Collector && Collector->GetCombat())
	{
		Collector->bDisableGameplay = true;
		Collector->GetCombat()->FireButtonPressed(false);
	}
}
