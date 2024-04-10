// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnLightOnOff.h"

// Sets default values
ATurnLightOnOff::ATurnLightOnOff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightSwitch"));

	RootComponent = CollisionComponent;
	SwitchMesh->SetupAttachment(RootComponent);
	LightState = ELightState::OFF;
}

// Called when the game starts or when spawned
void ATurnLightOnOff::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurnLightOnOff::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATurnLightOnOff::OnOverlapEnd);
}

void ATurnLightOnOff::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ATurnLightOnOff::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
// Called every frame
void ATurnLightOnOff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Tick(DeltaTime);
	if (on)
	{
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / TurnOnTime * 100.0f, 0.f, 100.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));
		float newYRotation;

		if (LightState == ELightState::OFF)
		{
			newYRotation = FMath::Lerp(45.0f, -45.0f, percentage / 100.0f);
		}
		else if (LightState == ELightState::ON)
		{
			newYRotation = FMath::Lerp(-45.0f, 45.0f, percentage / 100.0f);
		}

		FRotator  newRotation = SwitchMesh->GetRelativeRotation();

		newRotation.Roll = newYRotation;

		SwitchMesh->SetRelativeRotation(newRotation);



		if (percentage >= 100.0f)
		{
			on = false;
			timeSinceTick = 0;
			LightState = (LightState == ELightState::OFF) ? ELightState::ON : ELightState::OFF;
		}
	}
}
void ATurnLightOnOff::Use_Implementation() {
	on = true;
}

