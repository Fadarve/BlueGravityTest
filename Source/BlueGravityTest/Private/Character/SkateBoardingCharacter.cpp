// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateBoardingCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EnhancedInputComponent.h"

ASkateBoardingCharacter::ASkateBoardingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveForwardValue = 0.0f;
	
	Skateboard = CreateDefaultSubobject<USkeletalMeshComponent>("Skateboard");
	Skateboard->SetupAttachment(GetRootComponent());
}

void ASkateBoardingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABlueGravityTestCharacter::Look);
		
		// Moving
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASkateBoardingCharacter::TurnDirection);
		EnhancedInputComponent->BindAction(PushAction, ETriggerEvent::Triggered, this, &ASkateBoardingCharacter::Push);
		EnhancedInputComponent->BindAction(PushAction, ETriggerEvent::Completed, this, &ASkateBoardingCharacter::StopPushing);
		EnhancedInputComponent->BindAction(SlowDownAction, ETriggerEvent::Triggered, this, &ASkateBoardingCharacter::SlowDown);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

FRotator ASkateBoardingCharacter::TurnLeftRight()
{
	//add right-left movement
	FRotator NewRotation = FRotator::ZeroRotator;
	NewRotation.Yaw = MoveRightValue;
	AddActorLocalRotation(NewRotation);

	return NewRotation;
}

void ASkateBoardingCharacter::Push()
{
	if (Controller != nullptr)
	{
		// get forward vector
		const FVector ForwardDirection = Skateboard->GetForwardVector();

		if(!GetMovementComponent()->IsFalling())
		{
			MoveForwardValue = FMath::Lerp(MoveForwardValue,1.0f,MoveForwardAlpha);
			AddMovementInput(ForwardDirection, MoveForwardValue);
		}
	}
}

void ASkateBoardingCharacter::StopPushing()
{
	MoveForwardValue = 0.0f;
}

void ASkateBoardingCharacter::SlowDown()
{
	GetMovementComponent()->Velocity = FMath::Lerp(GetMovementComponent()->Velocity,FVector::Zero(),DecelerationFactor);
}

void ASkateBoardingCharacter::TurnDirection(const FInputActionValue& Value)
{
	// input is a Vector
	float MovementValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		/* add forward movement: If positive, accelerate the movement in the skateboard forward direction
		 * If negative, decelerate the movement by the decelerationFactor until 0
		 * */
		if(GetMovementComponent()->IsFalling())
		{
			MoveRightValue = MovementValue*MoveRightAirMultiplier;
			TurnLeftRight();
		}else
		{
			if(MoveForwardValue>0.0f) //Pushing forward
			{
				MoveRightValue = MovementValue*MoveRightMultiplier;
				TurnLeftRight();
			}else
			{
				MoveRightValue = MovementValue*MoveRightNoImpulseMultiplier;
				const FRotator direction = TurnLeftRight();
				GetMovementComponent()->Velocity = direction.RotateVector(GetMovementComponent()->Velocity);
			}
		}
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

bool ASkateBoardingCharacter::GetIsFalling()
{
	return GetMovementComponent()->IsFalling();
}



