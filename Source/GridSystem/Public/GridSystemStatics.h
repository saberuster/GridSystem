// Copyright saberuster. All Rights Reserved. 

#pragma once

#include "GridSystemSubsystem.h"
#include "GridSystemTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GridSystemStatics.generated.h"

/**
 * 
 */
UCLASS()
class GRIDSYSTEM_API UGridSystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
  	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GridSystemStatics")
	static void LocationToXYZ(const FVector& Translation, float WidthInCmScale, FIntVector& OutXYZ);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GridSystemStatics")
	static FGridElementID LocationToGridID(const FVector& Translation, float WidthInCmScale, const FIntVector& GridDimension);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GridSystemStatics")
	static void GridNumToXYZ(FGridElementID GridID, const FIntVector& GridDimension, FIntVector& OutXYZ);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GridSystemStatics")
	static FGridElementID XYZToGridID(const FIntVector& XYZ, const FIntVector& GridDimension);

	static UGridSystemSubsystem* GetGridSystemSubsystem(const UObject* WorldContextObject);

};
