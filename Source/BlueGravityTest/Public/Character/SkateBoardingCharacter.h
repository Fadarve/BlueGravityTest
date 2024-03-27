// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueGravityTest/BlueGravityTestCharacter.h"
#include "SkateBoardingCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BLUEGRAVITYTEST_API ASkateBoardingCharacter : public ABlueGravityTestCharacter
{
	GENERATED_BODY()

public:
	ASkateBoardingCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> Skateboard;

protected:
	virtual void Move(const FInputActionValue& Value) override;

private:
	float MoveForwardValue;
	float MoveRightValue;
	
	UPROPERTY(EditDefaultsOnly)
	float MoveForwardAlpha;

	UPROPERTY(EditDefaultsOnly)
	float MoveRightMultiplier;;
	
};
