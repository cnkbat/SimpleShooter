// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health=MaxHealth;
	Ammo =  MaxAmmo;
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	Gun->SetOwner(this);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"),this,&AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this,&AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);

	DamageToApply=FMath::Min(Health,DamageToApply);

	Health-=DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health= %f"),Health);
	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();

		if (GameMode!= nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->DestroyComponent();
		
		
	}
	
	return DamageToApply;
}	
//PlayerINPUTS
void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()* AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue* GetWorld()->GetDeltaSeconds() *RotationRate);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * GetWorld()->GetDeltaSeconds() * RotationRate);
}

//SHOOT
void AShooterCharacter::Shoot()
{
	if(GetAmmo()>0)
	{

	Gun->PullTrigger();

	Ammo--;
		
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	else 
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),NoAmmoSound,GetOwner()->GetActorLocation());
	}

}

bool AShooterCharacter::IsDead() const
{
	return Health<=0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health/MaxHealth;
}

int AShooterCharacter::GetAmmo() const
{
	return Ammo;
}