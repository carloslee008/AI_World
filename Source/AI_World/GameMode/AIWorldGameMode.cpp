// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWorldGameMode.h"

#include "AI_World/Character/Collector.h"
#include "AI_World/GameState/AIWorldGameState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "AI_World/PlayerController/AIWorldPlayerController.h"
#include "AI_World/PlayerState/AIWorldPlayerState.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");	
}

AAIWorldGameMode::AAIWorldGameMode()
{
	bDelayedStart = true;
}

void AAIWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void AAIWorldGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = CooldownTime + WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			RestartGame();
		}
	}
}

void AAIWorldGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AAIWorldPlayerController* AIWorldPlayer = Cast<AAIWorldPlayerController>(*It);
		if (AIWorldPlayer)
		{
			AIWorldPlayer->OnMatchStateSet(MatchState);
		}
	}
}

void AAIWorldGameMode::PlayerEliminated(ACollector* DownedCharacter, AAIWorldPlayerController* VictimController,
                                        AAIWorldPlayerController* AttackerController)
{
	if (AttackerController == nullptr || AttackerController->PlayerState == nullptr) return;
	if (VictimController == nullptr || VictimController->PlayerState == nullptr) return;
	AAIWorldPlayerState* AttackerPlayerState = AttackerController ? Cast<AAIWorldPlayerState>(AttackerController->PlayerState) : nullptr;
	AAIWorldPlayerState* VictimPlayerState = VictimController ? Cast<AAIWorldPlayerState>(VictimController->PlayerState) : nullptr;

	AAIWorldGameState* AIWorldGameState = GetGameState<AAIWorldGameState>();

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState && AIWorldGameState)
	{
		AttackerPlayerState->AddToScore(1.f);
		AIWorldGameState->UpdateTopScore(AttackerPlayerState);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDeaths(1);
	}
	if (DownedCharacter)
	{
		DownedCharacter->Down();
	}
}

void AAIWorldGameMode::RequestRevive(ACharacter* DownedCharacter, AController* DownedController)
{
	if (DownedCharacter)
	{
		DownedCharacter->Reset();
		DownedCharacter->Destroy();
	}
	if (DownedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(DownedController, PlayerStarts[Selection]);
	}
}