// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardTask::UBTTask_ClearBlackboardTask()
{
    NodeName= TEXT("Clear Blackboard Value");
}
EBTNodeResult::Type UBTTask_ClearBlackboardTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
