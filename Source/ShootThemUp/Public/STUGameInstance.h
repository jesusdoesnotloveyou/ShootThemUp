// Shoot Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    FLevelData GetStartupLevel() const { return StartupLevel; }
    void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }

    TArray<FLevelData> GetLevelData() const { return LevelsData; }

    FName GetMenuLevelName() const { return MenuLevelName; }
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "Levels' names must be unique!"))
    TArray<FLevelData> LevelsData;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

private:
    FLevelData StartupLevel;
};
