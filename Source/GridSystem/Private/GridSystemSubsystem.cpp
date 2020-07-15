// Copyright saberuster. All Rights Reserved. 

#include "GridSystemSubsystem.h"
#include "GridSystemSettings.h"
#include "GridSystemComponent.h"
#include "GridElement.h"

void UGridSystemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	bGridsInitialized = false;

	InitializeGrids();
}

void UGridSystemSubsystem::Deinitialize()
{
}

void UGridSystemSubsystem::InitializeGrids()
{
	check(!bGridsInitialized)
	GridElements.Reset();
	const UGridSystemSettings* Settings = GetDefault<UGridSystemSettings>();
	for (int32 GridElementID = 0; GridElementID < Settings->GetGridAmount(); ++GridElementID )
	{
		UGridElement* Element = NewObject<UGridElement>();
		Element->GridElementID = GridElementID;
		GridElements.Add(Element);
	}

	bGridsInitialized = true;	
}

UGridElement* UGridSystemSubsystem::LoadElement(const FGridElementID& GridElementID) const
{
	if (bGridsInitialized)
	{
		if (IsValidGridElementID(GridElementID))
		{
			return GridElements[GridElementID.IntID()];
		}
	}

	return nullptr;
}

bool UGridSystemSubsystem::IsValidGridElementID(const FGridElementID& GridElementID) const
{
	return GridElements.IsValidIndex(GridElementID.IntID());
}

bool UGridSystemSubsystem::RegisterGridSystemElements(UGridSystemComponent* GridSystemComponent)
{
	const TArray<FGridElementID>& GridElementIDs = GridSystemComponent->GetPlacementElementIDs();
	UGridElement* Element = nullptr;
	for (const FGridElementID& GridElementID : GridElementIDs)
	{
		if (!IsValidGridElementID(GridElementID))
		{
			return false;
		}
		Element = LoadElement(GridElementID);
		if (Element == nullptr)
		{
			return false;
		}
		if (Element->IsPossessedBy(GridSystemComponent))
		{
			continue;
		}
		if (!Element->IsEmpty())
		{
			return false;
		}
		
		Element->PossessedBy(GridSystemComponent);

		Element = nullptr;
	}

	return true;
}

bool UGridSystemSubsystem::UnRegisterGridSystemElements(UGridSystemComponent* GridSystemComponent)
{
	TArray<FGridElementID> GridElementIDs = GridSystemComponent->GetPlacementElementIDs();
	UGridElement* Element = nullptr;
	for (const FGridElementID& GridElementID : GridElementIDs)
	{
		if (!IsValidGridElementID(GridElementID))
		{
			return false;
		}

		Element = LoadElement(GridElementID);
		if (Element && Element->GridElementID == GridElementID && Element->IsPossessedBy(GridSystemComponent))
		{
			Element->Reset();
		}
		
		Element = nullptr;
	}

	return true;
}

bool UGridSystemSubsystem::CanRegisterGridSystemElements(UGridSystemComponent* GridSystemComponent, const TArray<FGridElementID>& WantRegisterIDs)
{
	UGridElement* Element = nullptr;
	for (const FGridElementID& GridElementID : WantRegisterIDs)
	{
		if (!IsValidGridElementID(GridElementID))
		{
			return false;
		}

		Element = LoadElement(GridElementID);

		if (!Element->IsEmpty())
		{
			if (!Element->IsPossessedBy(GridSystemComponent))
			{
				return false;
			}
		}
		
		Element = nullptr;
	}

	return true;
}


