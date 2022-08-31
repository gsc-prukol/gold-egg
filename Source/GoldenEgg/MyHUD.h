// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMessage {
	GENERATED_BODY()

	FString message;
	float time;
	FColor color;

	FMessage() {
		time = 5.f;
		color = FColor::White;
	}

	FMessage(FString iMessage, float iTime = 5.f, FColor iColor = FColor::White) {
		message = iMessage;
		time = iTime;
		color = iColor;
	}
};

UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;

	virtual void DrawHUD() override;
	void addMessage(FMessage msg);

private:
	TArray<FMessage> messages;
};

