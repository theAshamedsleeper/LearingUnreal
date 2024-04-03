// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_SpawnLocation.h"

// Sets default values
ABP_SpawnLocation::ABP_SpawnLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABP_SpawnLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_SpawnLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

