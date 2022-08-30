// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"

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
	AddControllerYawInput(RotationSpeed * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Pitch(float amount) {
	AddControllerPitchInput(RotationSpeed * amount * GetWorld()->GetDeltaSeconds());
}