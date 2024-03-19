// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AIWorldPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class AI_WORLD_API AAIWorldPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Replication notifies
	 */
	virtual void OnRep_Score() override;

	UFUNCTION()
	void OnRep_KilledBy();

	UFUNCTION()
	virtual void OnRep_Deaths();
	
	void AddToScore(float ScoreAmount);
	void AddToDeaths(int32 DeathsAmount);
	void UpdateDeathMessage();
private:
	UPROPERTY()
	class ACollector* Character;
	UPROPERTY()
	class AAIWorldPlayerController* Controller;

	UPROPERTY(ReplicatedUsing = OnRep_Deaths)
	int32 Deaths;

	UPROPERTY(ReplicatedUsing=OnRep_KilledBy)
	FString KilledBy;
	
};
