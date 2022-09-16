// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Avatar.h"
#include <Kismet/GameplayStatics.h>

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	canvasSizeX = Canvas->SizeX;
	canvasSizeY = Canvas->SizeY;

	DrawMessages();
	DrawHealthbar();
	DrawWidgets();
}

void AMyHUD::AddMessage(FMessage msg)
{
	messages.Add(msg);
}

void AMyHUD::AddWidget(FMyWidget wdg)
{
	FVector2D start(200, 200), pad(12, 12), size(100, 100);
	wdg.size = size;
	wdg.pos = start;

	for (int i = 0; i < widgets.Num(); i++) {
		wdg.pos.X += size.X + pad.X;

		if (wdg.pos.X + size.X > canvasSizeX) {
			wdg.pos.X = start.X;
			wdg.pos.Y += size.Y + pad.Y;
		}
	}

	widgets.Add(wdg);
}
void AMyHUD::ClearWidgets()
{
	widgets.Empty();
}

void AMyHUD::DrawMessages()
{
	for (int c = messages.Num() - 1; c >= 0; c--) {
		FMessage* msg = &messages[c];

		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(msg->message, outputWidth, outputHeight, hudFont);

		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;

		DrawRect(FLinearColor::Black, x, y, canvasSizeX, messageH);
		DrawTexture(msg->face, x, y, messageH, messageH, 0, 0, 1, 1);
		DrawText(msg->message, msg->color, x + pad + messageH, y + pad, hudFont);

		msg->time -= GetWorld()->GetDeltaSeconds();

		if (msg->time < 0) {
			messages.RemoveAt(c);
		}
	}
}

void AMyHUD::DrawHealthbar()
{
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	float barWidth = 200;
	float barHeight = 50;
	float barPad = 12;
	float barMargin = 50;

	float percHp = avatar->Hp/avatar->MaxHp;

	DrawRect(
		FLinearColor(0, 0, 0, 1),
		canvasSizeX - barWidth - barPad - barMargin,
		canvasSizeY - barHeight - barPad - barMargin,
		barWidth + 2 * barPad,
		barHeight + 2 * barPad
	);

	DrawRect(
		FLinearColor(1 - percHp, percHp, 0, 1),
		canvasSizeX - barWidth - barMargin,
		canvasSizeY - barHeight - barMargin,
		barWidth*percHp,
		barHeight
	);
}

void AMyHUD::DrawWidgets()
{
	for (auto& widget: widgets) {
		DrawTexture(widget.icon.tex, widget.pos.X, widget.pos.Y, widget.size.X, widget.size.Y, 0, 0, 1, 1);
		DrawText(widget.icon.name, FLinearColor::Yellow, widget.pos.X, widget.pos.Y, hudFont, .6f, false);
	}
}

void AMyHUD::MouseClicked()
{
	FVector2D mouse;
	PlayerOwner->GetMousePosition(mouse.X, mouse.Y);

	heldWidget = nullptr;

	for (auto& widget : widgets) {
		if (!widget.hit(mouse)) {
			
			continue;
		}

		heldWidget = &widget;
		return;
	}
}

void AMyHUD::MouseMoved()
{
	static FVector2D lastMouse;
	
	FVector2D thisMouse;
	PlayerOwner->GetMousePosition(thisMouse.X, thisMouse.Y);
	
	FVector2D dMouse = thisMouse - lastMouse;
	
	float time = PlayerOwner->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	
	if (time > 0.f && heldWidget) {
		heldWidget->pos += dMouse;
	}

	lastMouse = thisMouse;
}
