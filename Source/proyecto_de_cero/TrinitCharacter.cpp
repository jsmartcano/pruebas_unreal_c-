// Fill out your copyright notice in the Description page of Project Settings.

#include "TrinitCharacter.h"
#include "CoreMinimal.h"
#include "Engine.h"


// Sets default values
ATrinitCharacter::ATrinitCharacter()
{

	// Instanciar el esqueleto del player
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> mesha(TEXT("SkeletalMesh'/Game/MyContent/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(mesha.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	// Crear el objeto animación y ponerle el modo de animación
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> animBP(TEXT("AnimBlueprint'/Game/MyContent/UE4_Mannequin/Animations/CharAnimBP_1.CharAnimBP_1'"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(animBP.Object->GeneratedClass);

	// Crear el arma
	// ------------------------------------
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"), true);  // Crea el subobjeto
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("SkeletalMesh'/Game/MyContent/Weapons/FPWeapon/Mesh/SK_FPGun.SK_FPGun'")); // Obtiene el mesh
	if (WeaponMesh.Succeeded()) {
		Weapon->SetSkeletalMesh(WeaponMesh.Object); //Establece el esqueleto recuperado a nuestra variable de clase Weapon
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Skeletal Mesh Weapon no se he podido recuperar"));
	}
	

	// Crear el brazo de la cámara
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Crear la cámara
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));	
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	//GetMesh()->GetAnimInstance();
	

	// Desligar la rotación del controlador de la rotación del modelo
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Al mover el personaje, este rota hacia donde mira la cámara
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	IsWeaponEquip = false;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void ATrinitCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Atachar el arma al socket
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	Weapon->AttachToComponent(GetMesh(), AttachRules, FName("WeaponSocket"));
	Weapon->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	
	
}

void ATrinitCharacter::MoveForward(float Delta)
{
	if (Delta != 0.0f)
	{
		// Construye una matriz de rotación hacia donde mira el controlador
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

// Movimiento de la camara arriba/abajo -> pitch
void ATrinitCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * 45.f * GetWorld()->GetDeltaSeconds());
}


// Movimiento la cámara a los lados -> yaw
void ATrinitCharacter::Turn(float value)
{
	AddControllerYawInput(value * 45.f * GetWorld()->GetDeltaSeconds());
}

void ATrinitCharacter::EquipWeapon()
{
	IsWeaponEquip = true;
}

void ATrinitCharacter::UnequipWeapon()
{
	IsWeaponEquip = false;
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

	PlayerInputComponent->BindAction("EquipWeapon", EInputEvent::IE_Released, this, &ATrinitCharacter::EquipWeapon);
}

