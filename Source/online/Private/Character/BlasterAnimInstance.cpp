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
	bIsWeaponEquipped = BlasterChasracter->IsWeaponEquipped();
	bIsCrouched = BlasterChasracter->bIsCrouched;
	bAiming = BlasterChasracter->IsAiming();





	// Offset Yaw for Strafing
	FRotator AimRotation = BlasterChasracter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterChasracter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterChasracter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);


	AO_Yaw = BlasterChasracter->GetAO_Yaw();
	AO_Pitch = BlasterChasracter->GetAO_Pitch();

}
