// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkaterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,NotBlueprintable)
class USkaterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLUEGRAVITYTEST_API ISkaterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual float GetMoveForward() = 0;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetSKVelocity() = 0;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetSKBoardForward() = 0;

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsFalling() = 0;
};
