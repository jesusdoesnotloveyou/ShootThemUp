// Shoot Them Up Game, All Rights Reserved.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
    if (State == ESTUMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USTUGameOverWidget::UpdatePlayersStat()
{
    if (!GetWorld() || !PlayerStatBox) return;

    // To be sure that StatBox is empty from the begin
    PlayerStatBox->ClearChildren();
    
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;
        
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(this, PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}

void USTUGameOverWidget::OnResetLevel()
{
    //const FName CurrentLevelName = "TestLevel";
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    
    /*
     * You can also use the GameModeBase function ResetLevel, but it's implementation requires overriding
     * for all actors that exist at the level except GameModeBase and Controllers.
     * Or GETWORLD() instead of THIS (?).
    */
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}