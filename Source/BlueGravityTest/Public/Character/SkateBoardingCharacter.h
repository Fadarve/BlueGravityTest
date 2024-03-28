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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PushAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SlowDownAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TurnAction;

public:
	ASkateBoardingCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> Skateboard;

	UFUNCTION()
	virtual float GetMoveForward() override;

	UFUNCTION()
	virtual FVector GetSKVelocity() override;

	UFUNCTION()
	virtual FVector GetSKBoardForward() override;

	UFUNCTION()
	virtual bool GetIsFalling() override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	FRotator TurnLeftRight();

	void Push();
	void StopPushing();
	void SlowDown();
	void TurnDirection(const FInputActionValue& Value);

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
};
