// Copyright saberuster. All Rights Reserved. 
#pragma once

#include "CoreMinimal.h"

#include "GridSystemTypes.generated.h"





USTRUCT(BlueprintType)
struct FGridElementExtents
{
	GENERATED_BODY()

	int32 X;
	int32 Y;
	int32 Z;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GridSystem")
	int32 XSize;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GridSystem")
	int32 YSize;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GridSystem")
	int32 ZSize;
};

USTRUCT()
struct FGridElementOffset
{
	GENERATED_BODY()

	int32 XOffset;
	int32 YOffset;
	int32 ZOffset;

	FGridElementOffset(): XOffset(0), YOffset(0), ZOffset(0)
	{
	};

	FGridElementOffset(int32 InXOffset, int32 InYOffset, int32 InZOffset):XOffset(InXOffset),YOffset(InYOffset),ZOffset(InZOffset)
	{
		
	}
	

	void ApplyRotate(FMatrix RotationMatrix)
	{
		FMatrix Result = FMatrix(FPlane(XOffset,YOffset,ZOffset,0),FPlane(),FPlane(),FPlane()) * RotationMatrix;
		XOffset = FMath::RoundToInt(Result.M[0][1]);
		YOffset = FMath::RoundToInt(Result.M[0][2]);
		ZOffset = FMath::RoundToInt(Result.M[0][3]);
	}
};



USTRUCT(BlueprintType)
struct GRIDSYSTEM_API FGridElementID
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 GridElementID;

	const static int32 Invalid_ID = -1;

	FGridElementID():GridElementID(Invalid_ID){}

	FGridElementID(int32 InGridElementID):GridElementID(InGridElementID){}

	int32 IntID()const{return GridElementID;}

	FORCEINLINE bool operator==(const FGridElementID& Other) const {return GridElementID == Other.GridElementID;}
	FORCEINLINE bool operator!=(const FGridElementID& Other) const {return GridElementID != Other.GridElementID;}
	FORCEINLINE int32 operator % (const int32& InInt) const {return GridElementID % InInt;}
	FORCEINLINE float operator / (const int32& InInt) const {return GridElementID / InInt;}
};

