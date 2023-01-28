// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
void AKillThemAllGameMode::PawnKilled(APawn* Killed)
{
    Super::PawnKilled(Killed);
    APlayerController* PlayerController = Cast <APlayerController> (Killed->GetController());
    if ( PlayerController != nullptr)
    {
        EndGame(false);
    }

    for(AShooterAIController* Controller : TActorRange <AShooterAIController> (GetWorld()))
    {
        if(!Controller->IsDead()) 
        {
            return;
        } 
        EndGame(true); 
    }
       
        
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
    }
}