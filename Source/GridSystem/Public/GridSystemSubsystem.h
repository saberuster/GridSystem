// Copyright saberuster. All Rights Reserved. 

#pragma once

#include "GridSystemTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GridSystemSubsystem.generated.h"

class UGridSystemComponent;
class UGridElement;

/**
 * 
 */
UCLASS()
class GRIDSYSTEM_API UGridSystemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	void InitializeGrids();
    
	UGridElement* LoadElement(const FGridElementID& GridElementID) const;

	bool IsValidGridElementID(const FGridElementID& GridElementID) const;

	
	bool RegisterGridSystemElements(UGridSystemComponent* GridSystemComponent);
	bool UnRegisterGridSystemElements(UGridSystemComponent* GridSystemComponent);
	bool CanRegisterGridSystemElements( UGridSystemComponent* GridSystemComponent,const TArray<FGridElementID>& WantRegisterIDs);

	const TArray<UGridElement*>& GetGridElements() const {return GridElements;}

protected:
	
	UPROPERTY()
	TArray<UGridElement*> GridElements;

	UPROPERTY()
	bool bGridsInitialized;
};
