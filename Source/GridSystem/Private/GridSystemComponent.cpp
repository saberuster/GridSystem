// Copyright saberuster. All Rights Reserved. 


#include "GridSystemComponent.h"


#include "GridSystemSettings.h"
#include "GridSystemStatics.h"
#include "GridSystemSubsystem.h"

const FMatrixOfRotation UGridSystemComponent::No_Rotation = FMatrixOfRotation(EForceInit::ForceInitToZero);
const FMatrixOfRotation UGridSystemComponent::Rxz90 = FMatrixOfRotation(FVector(0,0,-1),
																		FVector(0,1,0),
																		FVector(1,0,0),
																		FVector::ZeroVector);
const FMatrixOfRotation UGridSystemComponent::Rxy90 = FMatrixOfRotation(FVector(0,1,0),
																		FVector(-1,0,0),
																		FVector(0,0,0),
																		FVector::ZeroVector);
const FMatrixOfRotation UGridSystemComponent::Ryz90 = FMatrixOfRotation(FVector(1,0,0),
																		FVector(0,0,1),
																		FVector(0,-1,0),
																		FVector::ZeroVector);


// Sets default values for this component's properties
UGridSystemComponent::UGridSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bAlreadyRegistered = false;
	ResetRotationMatrix();
}

void UGridSystemComponent::RefreshGridElementIDs()
{
	if (!bAlreadyRegistered)
	{
		TArray<FGridElementID> WantRegisterIDs;
    	FIntVector ElementCoordinateInGrid = FIntVector::ZeroValue;
    	const UGridSystemSettings* Settings = GetDefault<UGridSystemSettings>();
    	for (int32 ix =0; ix < GridElementExtents.XSize; ++ ix)
    	{
    		for (int32 iy = 0; iy < GridElementExtents.YSize; ++ iy)
    		{
    			for (int32 iz = 0; iz < GridElementExtents.ZSize; ++ iz)
    			{
    				const FGridElementOffset RotatedOffset = FGridElementOffset(ix,iy,iz, GridRotationMatrix);
    				RotatedOffset.OffsetCoordinate(ElementCoordinateInGrid);
    				FGridElementID ID = UGridSystemStatics::XYZToGridID(ElementCoordinateInGrid,Settings->GridDimension);
    				WantRegisterIDs.Add(ID);
    			}
    		}
    	}
    
    	
    	PlacementElementIDs.Reset();
    	PlacementElementIDs = WantRegisterIDs;	
	}
}

void UGridSystemComponent::PlaceActor()
{
	const FVector Location =  GetOwner()->GetActorLocation();
	FIntVector XYZ = FIntVector::ZeroValue;
	const UGridSystemSettings* Settings = GetDefault<UGridSystemSettings>();
	
	UGridSystemStatics::LocationToXYZ(Location,Settings->WidthInCm,XYZ);
	GridElementExtents.X = XYZ.X;
	GridElementExtents.Y = XYZ.Y;
	GridElementExtents.Z = XYZ.Z;
	RefreshGridElementIDs();
	RegisterToGridSystemSubsystem();
}

void UGridSystemComponent::ResetRotationMatrix()
{
	GridRotationMatrix = FMatrix(EForceInit::ForceInit);
}

void UGridSystemComponent::SetGridRotationMatrix(const FMatrixOfRotation& RotationMatrix)
{
	if (!bAlreadyRegistered)
	{
		GridRotationMatrix = RotationMatrix;
    	RefreshGridElementIDs();	
	}
}

void UGridSystemComponent::AppendRotationMatrix(const FMatrixOfRotation& RotationMatrix)
{
	check(true);
}


bool UGridSystemComponent::RegisterToGridSystemSubsystem()
{
	if (!bAlreadyRegistered)
	{
		if(UGridSystemSubsystem* GridSystemSubsystem = UGridSystemStatics::GetGridSystemSubsystem(this))
    	{
    		if(GridSystemSubsystem->RegisterGridSystemElements(this))
    		{
    			bAlreadyRegistered = true;
    			return true;
    		}
    	}	
	}
	
	checkNoEntry();
	return false;
}

bool UGridSystemComponent::UnRegisterFromGridSystemSubsystem()
{
	if (bAlreadyRegistered)
	{
		if(UGridSystemSubsystem* GridSystemSubsystem = UGridSystemStatics::GetGridSystemSubsystem(this))
    	{
    		return GridSystemSubsystem->UnRegisterGridSystemElements(this);
    	}	
	}
	
	checkNoEntry();
	return false;
}

// Called when the game starts
void UGridSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGridSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGridSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	UnRegisterFromGridSystemSubsystem();
	
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
