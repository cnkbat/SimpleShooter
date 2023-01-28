// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboardTask.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_ClearBlackboardTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public: 

	UBTTask_ClearBlackboardTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
