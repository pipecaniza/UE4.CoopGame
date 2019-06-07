// Fill out your copyright notice in the Description page of Project Settings.

#include "SGrenadeLauncher.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "SProjectile.h"
#include "DrawDebugHelpers.h"


void ASGrenadeLauncher::Fire()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		GetOwner()->GetActorEyesViewPoint(EyeLocation, EyeRotation); 

		FVector Location = MeshComp->GetSocketLocation(MuzzleSocketName);		

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Instigator = GetInstigator();
		ActorSpawnParams.Owner = this;

		FVector ShotDirection = EyeRotation.Vector();

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<ASProjectile>(ProjectileClass, Location, EyeRotation, ActorSpawnParams);
	}	
}