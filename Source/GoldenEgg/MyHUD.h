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
	UTexture2D* face;

	FMessage() {
		time = 5.f;
		color = FColor::White;
	}

	FMessage(FString iMessage, UTexture2D* iFace, float iTime = 5.f, FColor iColor = FColor::White) {
		message = iMessage;
		face = iFace;
		time = iTime;
		color = iColor;
	}
};

USTRUCT(BlueprintType)
struct FIcon {
	GENERATED_BODY()

	FString name;
	UTexture2D* tex;

	FIcon() {
		name = "UNKNOWN ICON";
		tex = nullptr;
	}

	FIcon(const FString& iName, UTexture2D* iTex) {
		name = iName;
		tex = iTex;
	}
};

USTRUCT(BlueprintType)
struct FMyWidget {
	GENERATED_BODY()

	FIcon icon;
	FVector2D pos, size;

	FMyWidget() {
	}
	
	FMyWidget(FIcon iIcon) {
		icon = iIcon;
	}

	float left() { return pos.X; }
	float right() { return pos.X + size.X; }

	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }
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
	void addWidget(FMyWidget wdg);
	void clearWidgets();

private:
	TArray<FMessage> messages;
	TArray<FMyWidget> widgets;

	void DrawMessages();
	void DrawHealthbar();
	void DrawWidgets();
};

