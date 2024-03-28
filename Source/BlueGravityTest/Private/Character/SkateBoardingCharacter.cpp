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

		/* add forward movement: If positive, accelerate the movement in the skateboard forward direction
		 * If negative, decelerate the movement by the decelerationFactor until 0
		 * */
		if(GetMovementComponent()->IsFalling())
		{
			MoveRightValue = MovementVector.X*MoveRightAirMultiplier;
			TurnLeftRight(MoveRightValue);
		}else
		{
			if(MovementVector.Y>0.0f) //Pushing forward
			{
				MoveForwardValue = FMath::Lerp(MoveForwardValue,MovementVector.Y,MoveForwardAlpha);
				AddMovementInput(ForwardDirection, MoveForwardValue);
				MoveRightValue = MovementVector.X*MoveRightMultiplier;
				TurnLeftRight(MoveRightValue);
			}else
			{
				if(MovementVector.Y<0.0f) //Decelrating
				{
					GetMovementComponent()->Velocity = FMath::Lerp(GetMovementComponent()->Velocity,FVector::Zero(),DecelerationFactor);
				}
				MoveRightValue = MovementVector.X*MoveRightNoImpulseMultiplier;
				const FRotator direction = TurnLeftRight(MoveRightValue);
				GetMovementComponent()->Velocity = direction.RotateVector(GetMovementComponent()->Velocity);
			}
		}
	}
}

FRotator ASkateBoardingCharacter::TurnLeftRight(float Amount)
{
	//add right-left movement
	FRotator NewRotation = FRotator::ZeroRotator;
	NewRotation.Yaw = MoveRightValue;
	AddActorLocalRotation(NewRotation);

	return NewRotation;
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

bool ASkateBoardingCharacter::GetIsFalling()
{
	return GetMovementComponent()->IsFalling();
}



