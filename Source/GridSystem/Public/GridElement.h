// Copyright saberuster. All Rights Reserved. 

#pragma once

#include "GridSystemTypes.h"

#include "GridElement.generated.h"


class UGridSystemComponent;
/**
 * 
 */
UCLASS()
class GRIDSYSTEM_API UGridElement : public UObject
{
	GENERATED_BODY()
public:

    UPROPERTY()
    FGridElementID GridElementID;
    
    virtual void Reset();
    FORCEINLINE bool IsEmpty() const { return GridElementID != FGridElementID::Invalid_ID; }
    void PossessedBy(UGridSystemComponent* InGridSystemComponent);
    bool IsPossessedBy(UGridSystemComponent* Other) const;

protected:
    
    TWeakObjectPtr<UGridSystemComponent> GridSystemComponent;
};
