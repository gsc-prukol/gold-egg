// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

// Sets default values
AMonster::AMonster(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Speed = 20.f;
    HitPoints = 20.f;
    Experience = 0;
    BPLoot = nullptr;
    BaseAttackDamage = 1.f;
    AttackTimeout = 1.5f;
    TimeSinceLastStrike = 0.f;

    SightSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
    SightSphere->AttachTo(RootComponent);

    AttackRangeSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
    AttackRangeSphere->AttachTo(RootComponent);
}
