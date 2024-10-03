// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlasterChasracter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABlasterChasracter::ABlasterChasracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;


	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABlasterChasracter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

}
//inputs

void ABlasterChasracter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// Obtém a rotação do controlador (câmera)
		const FRotator Rotation = Controller->GetControlRotation();

		// Obtém a rotação do plano XY
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Calcula as direções de movimento (frente e lado)
		const FVector DirectionForward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector DirectionRight = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Adiciona movimento nas direções calculadas
		AddMovementInput(DirectionForward, MovementVector.Y);
		AddMovementInput(DirectionRight, MovementVector.X);
	}
}
void ABlasterChasracter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// Limitar o pitch da câmera
		float NewPitch = Controller->GetControlRotation().Pitch + LookAxisVector.Y;
		NewPitch = FMath::Clamp(NewPitch, -60.f, 20.f);  // Ajuste os valores -80 e 80 conforme necessário

		// Aplicar rotação limitada
		Controller->SetControlRotation(FRotator(NewPitch, Controller->GetControlRotation().Yaw + LookAxisVector.X, 0.f));
	}

}
void ABlasterChasracter::Jump(const FInputActionValue& Value)
{
	Super::Jump();
}
//end inputs





void ABlasterChasracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlasterChasracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABlasterChasracter::Move);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABlasterChasracter::Look);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABlasterChasracter::Jump);

	}
}


