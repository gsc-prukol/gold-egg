// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int c = messages.Num() - 1; c >= 0; c--) {
		FMessage* msg = &messages[c];

		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(msg->message, outputWidth, outputHeight, hudFont);
		
		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;

		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		DrawText(msg->message, msg -> color, x + pad, y + pad, hudFont);
		
		msg->time -= GetWorld()->GetDeltaSeconds();
		
		if (msg->time < 0) {
			messages.RemoveAt(c);
		}
	}
}

void AMyHUD::addMessage(FMessage msg)
{
	messages.Add(msg);
}
