// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "Avatar.h"
#include <Kismet/GameplayStatics.h>
#include "MyHUD.h"

// Sets default values
APickupItem::APickupItem(const FObjectInitializer& ObjectInitializer) {
	Name = "UNKNOWN ITEM";
	Quantity = 0;

	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));

	RootComponent = Mesh;

	Mesh->SetSimulatePhysics(true);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
	ProxSphere->AttachTo(Mesh);

}

void APickupItem::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AAvatar>(OtherActor) == nullptr) {
		return;
	}

	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	avatar->Pickup(this);

	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	hud->AddMessage(FMessage(FString("Picked up") + FString::FromInt(Quantity) + Name, Icon));

	Destroy();
}