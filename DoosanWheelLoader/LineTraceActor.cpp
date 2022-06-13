// Fill out your copyright notice in the Description page of Project Settings.

// Project includes.
#include "LineTraceActor.h"
#include "LineTrace.h"

// AG Dynamics for Unreal includes.
#include "AGX_RigidBodyComponent.h"
#include "AGX_Simulation.h"

// Unreal Engine includes.
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

FSimulationBarrier* GetSimulationBarrier(AActor& Context)
{
	UAGX_Simulation* SimulationSubsystem = UAGX_Simulation::GetFrom(&Context);
	if (SimulationSubsystem == nullptr)
	{
		UE_LOG(
			LogTemp, Warning,
			TEXT("UDWL_DriveTrain: Got nullptr SimulationSubsystem. Cannot continue."));
		return nullptr;
	}

	FSimulationBarrier* SimulationBarrier = SimulationSubsystem->GetNative();
	if (SimulationBarrier == nullptr)
	{
		UE_LOG(
			LogTemp, Warning,
			TEXT("UDWL_DriveTrain: Got nullptr SimulationBarrier. Cannot continue"));
		return nullptr;
	}

	return SimulationBarrier;
}

ALineTraceActor::ALineTraceActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALineTraceActor::BeginPlay()
{
	Super::BeginPlay();
	horizongle = horizontal_FOV / points_per_line;
}

// Called every frame
void ALineTraceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FSimulationBarrier* SimulationBarrier = GetSimulationBarrier(*this);
	// std::vector<double> point_cloud;

	FLineTrace traceLine;
	point_cloud_base.clear();
	//point_cloud_World.clear();

	RayStart = GetActorLocation();
	ActorRotation = GetActorRotation();
	forwardVector = GetActorForwardVector();
	upVector = GetActorUpVector();
	rightVector = GetActorRightVector();

	ActorRotationPitch = ActorRotation.Pitch;
	ActorRotationYaw = ActorRotation.Yaw;
	ActorRotationRoll = ActorRotation.Roll;

	traceLine.LineTrace(
		SimulationBarrier,vertical_FOV,scan_lines,horizongle,points_per_line,
		forwardVector,upVector,rightVector,ActorRotationPitch,ActorRotationYaw,ActorRotationRoll, RayStart,
		forwardVector, point_cloud_base /*, point_cloud_World*/);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,FString::Printf(TEXT("POINTS NUMBER IS %d"), point_cloud_base.size(), true));
	/* for (size_t i = 0; i < point_cloud_World.size(); i++)
	{
		DrawDebugPoint(VisualMesh->GetWorld(), point_cloud_World[i], 3, FColor::Green, false, 0.0f);
	}*/
	
	/* memset(data, 0, 345600);
	for (size_t i = 0; i < point_cloud_base.size(); i++)
	{
		array[i] = reinterpret_cast<uint8_t*>(&point_cloud_base[i]);
		for (size_t j = 0; j < 4; j++)
		{
			data[i * 4 + j] = array[i][j];
		}
	}*/

	/*for (int j = 0; j < point_cloud.size(); j = j + 3)
	{
		FVector show_point(point_cloud[j], point_cloud[j + 1], point_cloud[j + 2]);
	}*/

	// Initialize a topic
	// UTopic* ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	// UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	// ExampleTopic->Init(
	//	rosinst->ROSIntegrationCore, TEXT("/velodyne_points"), TEXT("sensor_msgs/PointCloud2"));

	//// (Optional) Advertise the topic
	// ExampleTopic->Advertise();
	// pc.data_ptr = data;
	//// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Hello
	//// world, this is %d"), PointsArr.Num()), true);

	//// Publish a string to the topic

	// TSharedPtr<ROSMessages::sensor_msgs::PointCloud2> PointCloudMessage(
	//	new ROSMessages::sensor_msgs::PointCloud2(pc));
	// ExampleTopic->Publish(PointCloudMessage);
}
