// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// AGX Dynamics for Unreal includes.
//#include "AGX_RigidBodyReference.h"

// Unreal Engine includes.
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include<vector>
#include "DrawDebugHelpers.h"
#include "LineTraceActor.generated.h"

UCLASS()
class DOOSANWHEELLOADER_API ALineTraceActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALineTraceActor();
	//FSimulationBarrier* SimulationBarrier;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LidarConfig")
	float horizontal_FOV = 360.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LidarConfig")
	float vertical_FOV = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LidarConfig")
	int scan_lines = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LidarConfig")
	int points_per_line = 400;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LidarConfig")
	float scan_distance = 20000.0f;*/

	float horizongle;

	FVector RayStart;
	FVector RayDirection;

	FVector forwardVector;
	FVector upVector;
	FVector rightVector;
	
	//FVector pitchRotation;
	//FVector yawRotation;
	FRotator ActorRotation;
	float ActorRotationPitch;
	float ActorRotationYaw;
	float ActorRotationRoll;

	float calTime = 0;
	float targetTime = 0.1;
	int showTime = 0;

	std::vector<float> point_cloud_base;
	//std::vector<FVector> point_cloud_World;
	//FVector point;
	//FHitResult hit_result = FHitResult(ForceInit);
	//FCollisionQueryParams trace_params;
	//FVector EndLocation;

	uint8_t* array[86400];
	uint8_t data[345600];
	TArray<FString> PointsArr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

