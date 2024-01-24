// Shoot Them Up Game, All Rights Reserved.


#include "AI/Services/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIPerceptionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFindEnemyService, All, All);

USTUFindEnemyService::USTUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = STUUtils::GetSTUPlayerComponent<USTUAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            UE_LOG(LogFindEnemyService, Display, TEXT("Blackboard component is valid"));
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
