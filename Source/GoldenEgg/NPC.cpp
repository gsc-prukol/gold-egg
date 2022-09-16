// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "MyHUD.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 //	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity Sphere"));
	
	ProxSphere->InitSphereRadius(320.f);
	ProxSphere->AttachTo(RootComponent);
	
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	
	NpcMessage = "Hi, I'm Owen";
	Name = "Owen";
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
}

//(UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)
void ANPC::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr) {
		return;
	}

	APlayerController* PControler = GetWorld()->GetFirstPlayerController();

	if (!PControler) {
		return;
	}

	AMyHUD* hud = Cast<AMyHUD>(PControler->GetHUD());
	hud->AddMessage(FMessage(Name + FString(": ") + NpcMessage, Face));

	if (Item) {
		AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		avatar->Pickup(Item);
		Item->Destroy();
		Item = nullptr;
	}
}
