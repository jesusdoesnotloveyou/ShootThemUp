// Shoot Them Up Game, All Rights Reserved.


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRoundNum()
{
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum()
{
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining()
{
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode()
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState()
{
    // GetOwningPlayer is a function which allows to get widget owner!
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}