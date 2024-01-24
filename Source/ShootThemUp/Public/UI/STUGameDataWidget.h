// Shoot Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

class ASTUGameModeBase;
class ASTUPlayerState;

UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum();

    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum();

    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining();

private:
    ASTUGameModeBase* GetSTUGameMode();
	ASTUPlayerState* GetSTUPlayerState();
};
