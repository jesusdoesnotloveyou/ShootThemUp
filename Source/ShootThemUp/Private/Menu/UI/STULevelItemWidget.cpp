// Shoot Them Up Game, All Rights Reserved.

#include "STULevelItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USTULevelItemWidget::NativeOnInitialized() // Begin play for widgets
{
    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
    }
}

void USTULevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::SetLevelData(const FLevelData &Data)
{
    LevelData = Data;
    
    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelDisplayName));
    }
    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    }
}

void USTULevelItemWidget::SetSelected(bool IsSelected)
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}