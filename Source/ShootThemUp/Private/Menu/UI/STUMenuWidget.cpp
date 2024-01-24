// Shoot Them Up Game, All Rights Reserved.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/STULevelItemWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void USTUMenuWidget::InitLevelItems()
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    checkf(STUGameInstance->GetLevelData().Num() != 0, TEXT("Levels data array must not be empty"));

    if (!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : STUGameInstance->GetLevelData())
    {
        const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);
    
        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(STUGameInstance->GetLevelData()[0]);
    }
    else
    {
        OnLevelSelected(STUGameInstance->GetStartupLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData &Data)
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    STUGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void USTUMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
    if (Animation != HideAnimation) return;

    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnQuitGame()
{
    if (!GetWorld()) return;
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);

}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
