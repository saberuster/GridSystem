// Copyright saberuster. All Rights Reserved. 


#include "PlayerGridSystemComponent.h"


#include "GridElement.h"
#include "GridSystemSettings.h"
#include "GridSystemStatics.h"
#include "GridSystemSubsystem.h"

// Sets default values for this component's properties
UPlayerGridSystemComponent::UPlayerGridSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UPlayerGridSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerGridSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

