// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlasterAnimInstance.h"
#include "Character/BlasterChasracter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	BlasterChasracter = Cast<ABlasterChasracter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);


	if (BlasterChasracter == nullptr)
	{
		BlasterChasracter = Cast<ABlasterChasracter>(TryGetPawnOwner());
	}
	if (BlasterChasracter == nullptr) return;


	FVector Velocity = BlasterChasracter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = BlasterChasracter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = BlasterChasracter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;


}
