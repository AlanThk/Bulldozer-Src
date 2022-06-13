#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>

class FSimulationBarrier;

class AGXBARRIER_API FLineTrace
{
public:
	//static void SetSurfaceVelocity(FShapeBarrier* Barrier, const FVector& SurfaceVelocity);

	//input intersect's param , return collide points
	//
	void LineTrace(
		FSimulationBarrier* Barrier,const float& vertical_FOV,const int& scan_lines,const float& horizongle,const int& points_per_line, 
		const FVector& forwardVector, const FVector& upVector,const FVector& rightVector,
		const float& ActorRotationPitch,const float& ActorRotationYaw, const float& ActorRotationRoll, const FVector& RayStart,
		const FVector& RayDirection, std::vector<float>& point_cloud_base /*,
		std::vector<FVector>& point_cloud_World*/);
};
