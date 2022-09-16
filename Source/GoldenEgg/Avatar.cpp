// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "MyHUD.h"
#include "PickupItem.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);

	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
}

void AAvatar::MoveForward(float amount) {
	if (Controller && amount) {
		FVector fwd = GetActorForwardVector();

		AddMovementInput(fwd, amount);
	}
}

void AAvatar::MoveRight(float amount) {
	if (Controller && amount) {
		FVector right = GetActorRightVector();

		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw(float amount) {
	
	if (inventoryShowing) {
		GetHUD()->MouseMoved();
		return;
	}

	AddControllerYawInput(RotationSpeed * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Pitch(float amount) {
	
	if (inventoryShowing) {
		GetHUD()->MouseMoved();
		return;
	}
	
	AddControllerPitchInput(RotationSpeed * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::ToggleInventory()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	if (inventoryShowing) {
		hud->ClearWidgets();
		
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		
		return;
	}

	inventoryShowing = true;
	PController->bShowMouseCursor = true;

	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it) {
		FString fs = it->Key + FString::Printf(TEXT("x %d"), it->Value);
		UTexture2D* tex = Icons.Find(it->Key) ? Icons[it->Key] : nullptr;

		hud->AddWidget(FMyWidget(FIcon(fs, tex)));
	}
}

void AAvatar::MouseClicked()
{
	GetHUD()->MouseClicked();
}

AMyHUD* AAvatar::GetHUD()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	return hud;
}

void AAvatar::Pickup(APickupItem* item)
{
	if (Backpack.Find(item->Name)) {
		Backpack[item->Name] += item->Quantity;
		
		return;
	}

	Backpack.Add(item->Name, item->Quantity);
	Icons.Add(item->Name, item->Icon);
}
