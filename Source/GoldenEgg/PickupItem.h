// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "PickupItem.generated.h"

UCLASS()
class GOLDENEGG_API APickupItem : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	APickupItem(const FObjectInitializer& ObjectInitializer);

protected:


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Quantity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Item)
	USphereComponent* ProxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Item)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
