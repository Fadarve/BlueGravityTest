// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateBoardingCharacter.h"
#include "InputActionValue.h"

ASkateBoardingCharacter::ASkateBoardingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveForwardValue = 0.0f;
	
	Skateboard = CreateDefaultSubobject<USkeletalMeshComponent>("Skateboard");
	Skateboard->SetupAttachment(GetRootComponent());
}

void ASkateBoardingCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = Skateboard->GetForwardVector();
	
		// get right vector 
		const FVector RightDirection = Skateboard->GetRightVector();

		// add movement
		MoveForwardValue = FMath::Lerp(MoveForwardValue,MovementVector.Y,MoveForwardAlpha);
		AddMovementInput(ForwardDirection, MoveForwardValue);

		MoveRightValue = MovementVector.X*MoveRightMultiplier;
		AddMovementInput(RightDirection, MoveRightValue);
	}
}

