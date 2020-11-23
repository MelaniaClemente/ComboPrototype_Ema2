#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "ComboProrotype_Ema2CableSpline.generated.h"

UCLASS()
class COMBOPROTOTYPE_EMA2_API AComboProrotype_Ema2CableSpline : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Cable")
		USceneComponent* Root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable")
		USplineComponent* Spline;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable")
		UStaticMeshComponent* CurrentSocketStaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable")
		UStaticMesh* SocketStaticMesh;

	UPROPERTY(BlueprintReadWrite, EditANywhere, Category = "Cable")
		UStaticMesh* SplineStaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable")
		UMaterialInstance* Material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable", Meta = (ClampMin = 0.0f))
		float Size = 1.0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable", Meta = (ClampMin = -360.0f, ClampMax = 360.0f))
		FRotator SocketRotationOffset = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cable", Meta = (ClampMin = 0.0f))
		FVector SocketLocationOffset = FVector::ZeroVector;

public:	
	AComboProrotype_Ema2CableSpline();

	virtual void OnConstruction(const FTransform& Transform) override;
};
