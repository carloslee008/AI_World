// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_World/Interfaces/Interactables.h"
#include "GameFramework/Actor.h"
#include "Clue.generated.h"

UCLASS()
class AI_WORLD_API AClue : public AActor, public IInteractables
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Actor")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Actor")
	class UBoxComponent* BoxCollider;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Actor")
	class UTextRenderComponent* TextRender;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Audio")
	class UAudioComponent* Audio;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Audio")
	class USoundBase* SoundBase;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedActor, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	UFUNCTION()
	virtual void Investigate() override;
};
