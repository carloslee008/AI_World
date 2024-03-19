// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AIWorldGameMode.generated.h"

namespace MatchState
{
	extern AI_WORLD_API const FName Cooldown; // Match duration has been reached. Begin cooldown timer
}

/**
 * 
 */
UCLASS()
class AI_WORLD_API AAIWorldGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AAIWorldGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerEliminated(class ACollector* DownedCharacter, class AAIWorldPlayerController* VictimController, AAIWorldPlayerController* AttackerController);
	virtual void RequestRevive(class ACharacter* DownedCharacter, AController* DownedController);

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;
	
	float LevelStartingTime = 0.f;

protected:
	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;
	
private:
	float CountdownTime = 0.f;
public:
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }
};
