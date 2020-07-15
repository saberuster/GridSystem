#include "CoreMinimal.h"
#include "GridSystemStatics.h"
#include "Misc/AutomationTest.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGridSystemStaticsTest, "GridSystem.Statics", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FGridSystemStaticsTest::RunTest(const FString& Parameters)
{
    {
        FIntVector XYZ = FIntVector::ZeroValue;
        //UGridSystemStatics::LocationToXYZ(FVector(100.f,100.f,100.f), XYZ);
        TestEqual(TEXT("XYZ 1 1 1 Test"), XYZ,FIntVector(1,1,1));
    }
    
    return true;
}







