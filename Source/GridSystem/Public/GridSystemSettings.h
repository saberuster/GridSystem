/// Copyright saberuster. All Rights Reserved.

#pragma once

#include "GridSystemTypes.h"
#include "Engine/DeveloperSettings.h"
#include "GridSystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config = GridSystem, defaultconfig, meta=(DisplayName = "GridSystem"))
class GRIDSYSTEM_API UGridSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UGridSystemSettings();
	

    virtual FName GetCategoryName() const override;
	
	UPROPERTY(Config, EditAnywhere, Category = GridSystem)
	int32 WidthInCm;

	UPROPERTY(Config, EditAnywhere, Category = GridSystem)
	FIntVector GridDimension;

	FORCEINLINE int GetGridAmount() const {return GridDimension.X * GridDimension.Y * GridDimension.Z; }
    
};
