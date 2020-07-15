// Copyright saberuster. All Rights Reserved. 

#pragma once

#include "GridSystemComponent.h"
#include "GridSystemTypes.h"
#include "Components/ActorComponent.h"
#include "PlayerGridSystemComponent.generated.h"


class UGridElement;

UCLASS( ClassGroup=(GridSystem), meta=(BlueprintSpawnableComponent) )
class GRIDSYSTEM_API UPlayerGridSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UPlayerGridSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
