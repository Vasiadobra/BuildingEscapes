// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!PresurePlate)
	{

		UE_LOG(LogTemp, Error, TEXT(" %s is missing PresurePlate"), *GetWorld()->GetName())
	}
	

}

void UOpenDoor::OpenDoor()
{

	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 12.0f, 0.f));


}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (GetTotalMassOfActorsOnPlate() > 30.f)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if (!PresurePlate) { return TotalMass; }
	PresurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors)
	{
		TotalMass+= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
		
	}
	
	return TotalMass;
}

