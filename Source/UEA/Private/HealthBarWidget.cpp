// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::UpdateHealth(float NewHealth, float MaxHealth, float HealthChange)
{
	if (HealthBar)
	{
		float Ratio = (MaxHealth > 0.f) ? (NewHealth / MaxHealth) : 0.f;
		HealthBar->SetPercent(Ratio);

		// 체력이 낮아지면 바 색상 변경 (빨강-노랑-초록)
		FLinearColor BarColor = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, Ratio);
		HealthBar->SetFillColorAndOpacity(BarColor);
	}

	if (HealthText)
	{
		FString HpString = FString::Printf(TEXT("HP: %.0f / %.0f"), NewHealth, MaxHealth);
		HealthText->SetText(FText::FromString(HpString));
	}
}