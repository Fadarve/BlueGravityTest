// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FundamentalFunctions.generated.h"

/**
 * 
 */
UCLASS()
class BLUEGRAVITYTEST_API UFundamentalFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static float GetAngleTwoVectors(FVector V1, FVector V2);
};
