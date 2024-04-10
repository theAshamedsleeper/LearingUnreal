// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureZone.h"

// Sets default values
ACaptureZone::ACaptureZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	PoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole"));
	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));

	RootComponent = CollisionComponent;
	PoleMesh->SetupAttachment(RootComponent);
	FlagMesh->SetupAttachment(RootComponent);
	flagState = EFlagState::DOWN;

}

// Called when the game starts or when spawned
void ACaptureZone::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACaptureZone::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACaptureZone::OnOverlapEnd);
}

void ACaptureZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*capturing = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Colliding"));
	}*/
}

void ACaptureZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*capturing = false;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Not Colliding"));
	}*/
}

// Called every frame
void ACaptureZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (capturing)
	{
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / CaptureTime * 100.0f, 0.f, 100.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));
		float newZPos;

		if (flagState == EFlagState::DOWN)
		{
			newZPos = FMath::Lerp(-16.0f, 28.0f, percentage / 100.0f);
		}
		else if(flagState == EFlagState::UP)
		{
			newZPos = FMath::Lerp(28.0f, -16.0f, percentage / 100.0f);
		}

		FVector newLocation = FlagMesh->GetRelativeLocation();
		
		newLocation.Z = newZPos;

		FlagMesh->SetRelativeLocation(newLocation);
		


		if (percentage >= 100.0f)
		{
			capturing = false;
			timeSinceTick = 0;
			flagState = (flagState == EFlagState::DOWN) ? EFlagState::UP : EFlagState::DOWN;
		}
	}

}

void ACaptureZone::Use_Implementation(){
	capturing = true;
}

