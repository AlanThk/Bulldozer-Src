#include "LineTrace.h"

//#include "AgxApiAccess_LogCategory.h"

// AGX Dynamics includes.
#include "BeginAGXIncludes.h"
#include <agxCollide/Geometry.h>
#include "EndAGXIncludes.h"

// AGXUnreal includes.
#include "Shapes/ShapeBarrier.h"
#include "AGX_AgxDynamicsObjectsAccess.h"
#include "TypeConversions.h"

void FLineTrace::LineTrace(
	FSimulationBarrier* Barrier, const float& vertical_FOV, const int& scan_lines,const float& horizongle, const int& points_per_line,
	const FVector& forwardVector,const FVector& upVector, const FVector& rightVector,
	const float& ActorRotationPitch,const float& ActorRotationYaw, const float& ActorRotationRoll, const FVector& RayStart,
	const FVector& RayDirection, std::vector<float>& point_cloud_base /*,
	std::vector<FVector>& point_cloud_World*/)
{
	agxCollide::LocalGeometryContactVector GVector;
	agxCollide::LocalParticleGeometryContactVector PVector;

	agxSDK::Simulation* Simulation = FAGX_AgxDynamicsObjectsAccess::GetFrom(Barrier);
	agxCollide::Space* Space = Simulation->getSpace();

	agx::Vec3 RayStartAGX = ConvertDisplacement(RayStart);
	agx::Vec3 RayDirectionAGX = ConvertVector(RayDirection);

	for (float y = (vertical_FOV / 2); y > -(vertical_FOV / 2); y -= (vertical_FOV / scan_lines))
	{
		FVector pitchRotation = forwardVector.RotateAngleAxis(y, rightVector);
		for (int z = 0; z < points_per_line; z++)
		{
			FVector yawRotation = pitchRotation.RotateAngleAxis(z * horizongle, upVector);
			Space->intersect(RayStartAGX, RayDirectionAGX, GVector, PVector, 100);
			//FVector hitPoint(0, 0, 0); 
			if (GVector.size() != 0)
			{
				agx::Vec3& pointAGX = GVector[0].points()[0].point();
				FVector hitPoint = ConvertDisplacement(pointAGX);
				//point_cloud_World.emplace_back(hitPoint);
				FVector vectorRoll =(hitPoint - RayStart).RotateAngleAxis(ActorRotationPitch, rightVector);
				FVector vectorPitch = vectorRoll.RotateAngleAxis(-ActorRotationYaw, upVector);
				FVector vectorYaw = vectorPitch.RotateAngleAxis(ActorRotationRoll, forwardVector);
				point_cloud_base.emplace_back(vectorYaw.X / 100);
				point_cloud_base.emplace_back(-vectorYaw.Y / 100);
				point_cloud_base.emplace_back(vectorYaw.Z / 100);
			}
		}
	}
}
