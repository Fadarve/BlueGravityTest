// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/FundamentalFunctions.h"

#include "Kismet/KismetMathLibrary.h"

float UFundamentalFunctions::GetAngleTwoVectors(FVector V1, FVector V2)
{
	return UKismetMathLibrary::DegAcos(UKismetMathLibrary::Dot_VectorVector(V1,V2)/V1.Length()*V2.Length());
}
