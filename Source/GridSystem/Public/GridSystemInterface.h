// Copyright saberuster. All Rights Reserved. 

#pragma once

#include "GridSystemTypes.h"
#include "GridSystemComponent.h"
#include "UObject/Interface.h"
#include "GridSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,meta = (CannotImplementInterfaceInBlueprint))
class UGridSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GRIDSYSTEM_API IGridSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UGridSystemComponent* GetGridSystemComponent() const = 0;
};
