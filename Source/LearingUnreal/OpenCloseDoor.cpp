// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCloseDoor.h"

// Sets default values
AOpenCloseDoor::AOpenCloseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	RootComponent = CollisionComponent;
	DoorMesh->SetupAttachment(RootComponent);
	doorState = EDoorState::CLOSED;
}

// Called when the game starts or when spawned
void AOpenCloseDoor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AOpenCloseDoor::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AOpenCloseDoor::OnOverlapEnd);
}
void AOpenCloseDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AOpenCloseDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called every frame
void AOpenCloseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	if (opening)
	{
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / OpeningTime * 100.0f, 0.f, 100.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));
		float newZRotation;

		if (doorState == EDoorState::CLOSED)
		{
			newZRotation = FMath::Lerp(0.0f, 90.0f, percentage / 100.0f);
		}
		else if (doorState == EDoorState::OPEN)
		{
			newZRotation = FMath::Lerp(90.0f, 0.0f, percentage / 100.0f);
		}

		FRotator  newRotation = DoorMesh->GetRelativeRotation();

		newRotation.Yaw = newZRotation;

		DoorMesh->SetRelativeRotation(newRotation);



		if (percentage >= 100.0f)
		{
			opening = false;
			timeSinceTick = 0;
			doorState = (doorState == EDoorState::CLOSED) ? EDoorState::OPEN : EDoorState::CLOSED;
		}
	}
}
void AOpenCloseDoor::Use_Implementation() {
	opening = true;
}

