// Copyright saberuster. All Rights Reserved. 


#include "GridSystemSettings.h"


UGridSystemSettings::UGridSystemSettings()
    :WidthInCm(100),GridDimension(10,10,2)
{
}

FName UGridSystemSettings::GetCategoryName() const
{
    return FName(TEXT("Plugins"));
}

