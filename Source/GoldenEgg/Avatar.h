// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem;
class AMyHUD;

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HP)
	float MaxHp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	float Hp = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FString, int> Backpack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FString, UTexture2D*> Icons;

	bool inventoryShowing;

	void Pickup(APickupItem* item);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amount);
	void MoveRight(float amount);

	void Yaw(float amount);
	void Pitch(float amount);

	void ToggleInventory();

	void MouseClicked();
private:
	AMyHUD* GetHUD();
};
