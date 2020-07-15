// Copyright saberuster. All Rights Reserved. 

#pragma once

#include "GridSystemTypes.h"
#include "Components/ActorComponent.h"
#include "GridSystemComponent.generated.h"


UCLASS( ClassGroup=(GridSystem), meta=(BlueprintSpawnableComponent) )
class GRIDSYSTEM_API UGridSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	static const FMatrix Rxz90;

	// Sets default values for this component's properties
	UGridSystemComponent();

protected:
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="GridSystem")
	FGridElementExtents GridElementExtents;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="GridSystem")
	TArray<FGridElementID> PlacementElementIDs;

	UPROPERTY()
	FMatrix GridRotationMatrix;

	UPROPERTY()
	bool bAlreadyRegistered;
	
public:

	UFUNCTION(BlueprintCallable,Category="GridSystem")
	void PlaceActor();
	
	void SetGridRotationMatrix(const FMatrix& RotationMatrix);
	
	const TArray<FGridElementID>& GetPlacementElementIDs() const {return PlacementElementIDs;}

	bool IsAlreadyRegistered() const {return bAlreadyRegistered;}

	bool RegisterToGridSystemSubsystem();
	bool UnRegisterFromGridSystemSubsystem();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    	
	void RefreshGridElementIDs();
		
};
