// Copyright saberuster. All Rights Reserved. 


#include "GridElement.h"

void UGridElement::Reset()
{
    GridElementID = FGridElementID::Invalid_ID;
    GridSystemComponent.Reset();
}

void UGridElement::PossessedBy(UGridSystemComponent* InGridSystemComponent)
{
    GridSystemComponent = InGridSystemComponent;
}

bool UGridElement::IsPossessedBy(UGridSystemComponent* Other) const
{
    if (GridSystemComponent != nullptr)
    {
        if (GridSystemComponent.IsValid() && GridSystemComponent.Get() == Other)
        {
            return true;
        }
    }
    return false;
}

