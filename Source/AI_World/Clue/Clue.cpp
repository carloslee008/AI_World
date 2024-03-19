// Fill out your copyright notice in the Description page of Project Settings.


#include "Clue.h"

#include "AI_World/Interfaces/Interactables.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AClue::AClue()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->SetBoxExtent(FVector(100.f, 100.f, 100.f), false);
	BoxCollider->SetupAttachment(Mesh);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Investigate"));
	TextRender->SetupAttachment(Mesh);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	

}

// Called when the game starts or when spawned
void AClue::BeginPlay()
{
	Super::BeginPlay();

	TextRender->SetHiddenInGame(true);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AClue::OverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AClue::OverlapEnd);
	
}

void AClue::OverlapBegin(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	bool DoesImplementInterface = OtherActor->Implements<UInteractables>();
	
	if (DoesImplementInterface)
	{
		TextRender->SetHiddenInGame(false);
	}
}

void AClue::OverlapEnd(UPrimitiveComponent* OverlappedActor, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	bool DoesImplementInterface = OtherActor->Implements<UInteractables>();

	if (DoesImplementInterface)
	{
		TextRender->SetHiddenInGame(true);
	}
}

void AClue::Investigate()
{
	if (!Audio->IsPlaying())
	{
		Audio->SetSound(SoundBase);
		Audio->Play();
	}
}



