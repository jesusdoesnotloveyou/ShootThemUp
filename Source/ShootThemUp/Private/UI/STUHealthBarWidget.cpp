// Shoot Them Up Game, All Rights Reserved.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar) return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityTheshold || FMath::IsNearlyZero(Percent)) //
        ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);
    
    const auto HealthBarColor = Percent > PercentColorTheshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}