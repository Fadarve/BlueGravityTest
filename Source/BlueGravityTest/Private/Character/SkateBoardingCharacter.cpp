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
		if(MovementVector.Y>0.0f)
		{
			MoveForwardValue = FMath::Lerp(MoveForwardValue,MovementVector.Y,MoveForwardAlpha);
			AddMovementInput(ForwardDirection, MoveForwardValue);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Forward movement 0"));
			MoveRightValue = MovementVector.X*MoveRightMultiplier;
		}else
		{
			GetMovementComponent()->Velocity = FMath::Lerp(GetMovementComponent()->Velocity,FVector::Zero(),DecelerationFactor);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Forward movement less 0"));
			MoveRightValue = MovementVector.X*MoveRightNoImpulseMultiplier;
		}
		
		//add right-left movement
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



