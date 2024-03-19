// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AIWorldGameState.generated.h"

class AAIWorldPlayerState;
/**
 * 
 */
UCLASS()
class AI_WORLD_API AAIWorldGameState : public AGameState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void UpdateTopScore(AAIWorldPlayerState* ScoringPlayer);
	
	UPROPERTY(Replicated)
	TArray<AAIWorldPlayerState*> TopScoringPlayers;
private:
	float TopScore = 0.f;
};
