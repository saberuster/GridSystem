// Copyright saberuster. All Rights Reserved. 


#include "GridSystemStatics.h"


void UGridSystemStatics::LocationToXYZ(const FVector& Translation,float WidthInCmScale, FIntVector& OutXYZ)
{
    OutXYZ.X = FMath::CeilToInt(Translation.X * WidthInCmScale);
    OutXYZ.Y = FMath::CeilToInt(Translation.Y * WidthInCmScale);
    OutXYZ.Z = FMath::CeilToInt(Translation.Z * WidthInCmScale);
}

FGridElementID UGridSystemStatics::LocationToGridID(const FVector& Translation, float WidthInCmScale, const FIntVector& GridDimension)
{
    FIntVector XYZ = FIntVector::ZeroValue;
    LocationToXYZ(Translation, WidthInCmScale, XYZ);
    return XYZToGridID(XYZ, GridDimension);
}


void UGridSystemStatics::GridNumToXYZ(FGridElementID GridElementID, const FIntVector& GridDimension, FIntVector& OutXYZ)
{
    const int32 Temp = GridElementID % (GridDimension.X * GridDimension.Y);
    const int32 Temp2 = Temp % GridDimension.X;
    OutXYZ.X = Temp2 == 0 ? GridDimension.X : Temp2;
    OutXYZ.Y = FMath::CeilToInt(Temp / GridDimension.X);
    OutXYZ.Z = FMath::CeilToInt( GridElementID / (GridDimension.X * GridDimension.Y));
}

FGridElementID UGridSystemStatics::XYZToGridID(const FIntVector& XYZ, const FIntVector& GridDimension)
{
    return FGridElementID(XYZ.X + XYZ.Y * GridDimension.X + XYZ.Z * GridDimension.X * GridDimension.Y);
}

UGridSystemSubsystem* UGridSystemStatics::GetGridSystemSubsystem(const UObject* WorldContextObject)
{
    if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull))
    {
        return UGameInstance::GetSubsystem<UGridSystemSubsystem>(World->GetGameInstance());
    }
    return nullptr;
}
