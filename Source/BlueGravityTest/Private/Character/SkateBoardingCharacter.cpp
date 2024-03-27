// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateBoardingCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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
		// get forward vector
		const FVector ForwardDirection = Skateboard->GetForwardVector();
	
		// get right vector 
		const FVector RightDirection = Skateboard->GetRightVector();

		// add forward movement
		if(MovementVector.Y>0.0f)
		{
			MoveForwardValue = FMath::Lerp(MoveForwardValue,MovementVector.Y,MoveForwardAlpha);
			AddMovementInput(ForwardDirection, MoveForwardValue);
		}else
		{
			if(GetMovementComponent()->Velocity.Length()>0.0f)
			{
				AddMovementInput(ForwardDirection,MovementVector.Y*DecelerationFactor);
			}
		}
		
		//add right-left movement
		MoveRightValue = MovementVector.X*MoveRightMultiplier;
		AddMovementInput(RightDirection, MoveRightValue);
	}
}

float ASkateBoardingCharacter::GetMoveForward()
{
	return MoveForwardValue;
}

FVector ASkateBoardingCharacter::GetSKVelocity()
{
	return GetCharacterMovement()->Velocity;
}

FVector ASkateBoardingCharacter::GetSKBoardForward()
{
	return Skateboard->GetForwardVector();
}



