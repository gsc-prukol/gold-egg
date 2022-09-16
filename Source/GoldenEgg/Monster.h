// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/SphereComponent.h>
#include "Monster.generated.h"

UCLASS()
class GOLDENEGG_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster(const FObjectInitializer& ObjectInitializer);

protected:


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float HitPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 Experience;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPLoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float AttackTimeout;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastStrike;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* AttackRangeSphere;
};
