// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWorldPlayerState.h"

#include "AI_World/Character/Collector.h"
#include "AI_World/PlayerController/AIWorldPlayerController.h"
#include "Net/UnrealNetwork.h"

void AAIWorldPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAIWorldPlayerState, Deaths);
	DOREPLIFETIME(AAIWorldPlayerState, KilledBy);
}

void AAIWorldPlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);
	Character = Character == nullptr ? Cast<ACollector>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AAIWorldPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void AAIWorldPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<ACollector>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AAIWorldPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void AAIWorldPlayerState::AddToDeaths(int32 DeathsAmount)
{
	Deaths += DeathsAmount;
	Character = Character == nullptr ? Cast<ACollector>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AAIWorldPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeaths(Deaths);
		}
	}
}

void AAIWorldPlayerState::OnRep_Deaths()
{
	Character = Character == nullptr ? Cast<ACollector>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AAIWorldPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeaths(Deaths);
		}
	}
}

void AAIWorldPlayerState::UpdateDeathMessage()
{
	Character = Character == nullptr ? Cast<ACollector>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AAIWorldPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeathScreen(KilledBy);
		}
	}
}


void AAIWorldPlayerState::OnRep_KilledBy()
{
	UpdateDeathMessage();
}