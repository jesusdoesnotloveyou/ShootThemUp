// Shoot Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    void SetHealthPercent(float Percent);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisibilityTheshold = 0.8f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorTheshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;
};
