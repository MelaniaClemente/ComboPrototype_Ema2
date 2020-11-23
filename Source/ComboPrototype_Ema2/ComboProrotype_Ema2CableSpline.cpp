#include "ComboProrotype_Ema2CableSpline.h"

#define PRINT_ONE GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,

AComboProrotype_Ema2CableSpline::AComboProrotype_Ema2CableSpline()
{
	bRunConstructionScriptOnDrag = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Root->AttachTo(RootComponent);

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->AttachTo(Root);

	CurrentSocketStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("SocketStaticMesh");
	CurrentSocketStaticMesh->AttachTo(Root);

	
}

void AComboProrotype_Ema2CableSpline::OnConstruction(const FTransform& Transform)
{
	CurrentSocketStaticMesh->SetStaticMesh(SocketStaticMesh);

	Spline->SetRelativeScale3D(FVector(Size, Size, Size));

	for (int i = 0; i < Spline->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* CurrentSplineMesh = NewObject<USplineMeshComponent>(this, *("Segment_" + FString::FromInt(i)));
		CurrentSplineMesh->SetMobility(EComponentMobility::Movable);
		CurrentSplineMesh->SetStaticMesh(SplineStaticMesh);
		CurrentSplineMesh->SetMaterial(0, Material);
		CurrentSplineMesh->AttachTo(Root);
		CurrentSplineMesh->SetForwardAxis(ESplineMeshAxis::Z, true);
		FVector StartLocation, StartTangent, EndLocation, EndTangent;
		Spline->GetLocationAndTangentAtSplinePoint(i, StartLocation, StartTangent, ESplineCoordinateSpace::Local);
		Spline->GetLocationAndTangentAtSplinePoint(i + 1, EndLocation, EndTangent, ESplineCoordinateSpace::Local);
		CurrentSplineMesh->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent, true);
	
		RegisterAllComponents();

		if (i == Spline->GetNumberOfSplinePoints() - 2)
		{
			CurrentSocketStaticMesh->SetRelativeRotation(SocketRotationOffset);
			CurrentSocketStaticMesh->SetRelativeLocation(EndLocation + SocketLocationOffset);
		}
	}
}