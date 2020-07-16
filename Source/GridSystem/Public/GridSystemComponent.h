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

	static const FMatrixOfRotation No_Rotation;
	static const FMatrixOfRotation Rxz90; // xz plane rotation
	static const FMatrixOfRotation Rxy90; // xy plane rotation
	static const FMatrixOfRotation Ryz90; // yz plane rotation

	// Sets default values for this component's properties
	UGridSystemComponent();

protected:
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="GridSystem")
	FGridElementExtents GridElementExtents;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="GridSystem")
	TArray<FGridElementID> PlacementElementIDs;

	FMatrixOfRotation GridRotationMatrix;

	bool bAlreadyRegistered;
	
public:

	UFUNCTION(BlueprintCallable,Category="GridSystem")
	void PlaceActor();

	void ResetRotationMatrix();
	void SetGridRotationMatrix(const FMatrixOfRotation& RotationMatrix);
	void AppendRotationMatrix(const FMatrixOfRotation& RotationMatrix);
	
	const TArray<FGridElementID>& GetPlacementElementIDs() const {return PlacementElementIDs;}

	bool IsAlreadyRegistered() const {return bAlreadyRegistered;}

	bool RegisterToGridSystemSubsystem();
	bool UnRegisterFromGridSystemSubsystem();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    	
	void RefreshGridElementIDs();

};
