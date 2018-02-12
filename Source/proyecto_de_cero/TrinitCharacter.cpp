// Fill out your copyright notice in the Description page of Project Settings.

#include "TrinitCharacter.h"
#include "Engine.h"

// Sets default values
ATrinitCharacter::ATrinitCharacter()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> mesha(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(mesha.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));	
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	

	// Desligar la rotación del controlador de la rotación del modelo
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Al mover el personaje, este rota hacia donde mira la cámara
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	/*Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");
	Mesh2->SetupAttachment(RootComponent);

	Mesh2->OnComponentBeginOverlap.AddDynamic(this, &ATrinitCharacter::OnOverlap);*/

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATrinitCharacter::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, "Hello");
}

// Called when the game starts or when spawned
void ATrinitCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATrinitCharacter::MoveForward(float Delta)
{
	if (Delta != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Delta);
	}
}

void ATrinitCharacter::MoveRight(float Delta)
{
	if (Delta != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Delta);
	}
}

void ATrinitCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * 45.f * GetWorld()->GetDeltaSeconds());
}

void ATrinitCharacter::Turn(float value)
{
	AddControllerYawInput(value * 45.f * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void ATrinitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Green, FString::SanitizeFloat(DeltaTime));
}

// Called to bind functionality to input
void ATrinitCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATrinitCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATrinitCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);	
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("LookUp", this, &ATrinitCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ATrinitCharacter::Turn);
}

