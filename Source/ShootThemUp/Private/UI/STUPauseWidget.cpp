// Shoot Them Up Game, All Rights Reserved.


#include "UI/STUPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"
#include "STUGameModeBase.h"

bool USTUPauseWidget::Initialize()
{
    // Instead of Initialize we can use the NativeOnInitialized as in the STUGameOverWidget.cpp and STUGameHUD.cpp
    const auto InitStatus = Super::Initialize();
    // Adding callback to button click event (!)
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }
    return InitStatus;
}

void USTUPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}