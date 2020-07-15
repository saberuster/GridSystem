// Copyright saberuster. All Rights Reserved. 


#include "GridSystemComponent.h"


#include "GridSystemSettings.h"
#include "GridSystemStatics.h"
#include "GridSystemSubsystem.h"

const FMatrix UGridSystemComponent::Rxz90 = FMatrix(FVector(0,0,-1),FVector(0,1,0),FVector(1,0,0),FVector::ZeroVector);


// Sets default values for this component's properties
UGridSystemComponent::UGridSystemComponent()
	:bAlreadyRegistered(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGridSystemComponent::RefreshGridElementIDs()
{
	if (!bAlreadyRegistered)
	{
		TArray<FGridElementID> WantRegisterIDs;
    	FIntVector XYZ = FIntVector::ZeroValue;
    	const UGridSystemSettings* Settings = GetDefault<UGridSystemSettings>();
    	for (int32 ix =0; ix < GridElementExtents.XSize; ++ ix)
    	{
    		for (int32 iy = 0; iy < GridElementExtents.YSize; ++ iy)
    		{
    			for (int32 iz = 0; iz < GridElementExtents.ZSize; ++ iz)
    			{
    				FGridElementOffset Offset = FGridElementOffset(ix,iy,iz);
    				Offset.ApplyRotate(GridRotationMatrix);
    				XYZ.X = GridElementExtents.X + Offset.XOffset;
    				XYZ.Y = GridElementExtents.Y + Offset.YOffset;
    				XYZ.Z = GridElementExtents.Z + Offset.ZOffset;
    				FGridElementID ID = UGridSystemStatics::XYZToGridID(XYZ,Settings->GridDimension);
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

void UGridSystemComponent::SetGridRotationMatrix(const FMatrix& RotationMatrix)
{
	if (!bAlreadyRegistered)
	{
		GridRotationMatrix = RotationMatrix;
    	RefreshGridElementIDs();	
	}
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
