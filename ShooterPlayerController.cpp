// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
AShooterPlayerController::AShooterPlayerController()
{
    
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUD = CreateWidget(this,PlayerHUD);
    if (HUD!=nullptr)
    {
        HUD->AddToViewport();
    }
    
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);
    if (bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this,WinScreenClass);
        if (WinScreen!=nullptr)
        {
            WinScreen->AddToViewport();
        }
        
    }
    
    else
    {
    UUserWidget* LoseScreen = CreateWidget(this,LoseScreenClass);

        if (LoseScreen!=nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
    HUD->RemoveFromViewport();
    GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
    
}