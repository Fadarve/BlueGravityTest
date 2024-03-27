// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkaterInterface.h"
#include "BlueGravityTest/BlueGravityTestCharacter.h"
#include "SkateBoardingCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BLUEGRAVITYTEST_API ASkateBoardingCharacter : public ABlueGravityTestCharacter, public ISkaterInterface
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
	float MoveRightMultiplier;

	UPROPERTY(EditDefaultsOnly)
	float MoveRightNoImpulseMultiplier;
	
	UPROPERTY(EditDefaultsOnly)
	float MoveRightAirMultiplier;

	UPROPERTY(EditDefaultsOnly)
	float DecelerationFactor;

public:
	UFUNCTION(BlueprintCallable)
	virtual float GetMoveForward() override;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetSKVelocity() override;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetSKBoardForward() override;
};
