// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"

#include "GameFramework/Character.h"
#include "TrinitCharacter.generated.h"


UCLASS()
class PROYECTO_DE_CERO_API ATrinitCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Trinit")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Trinit")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Trinit")
	USkeletalMeshComponent* Weapon;

	bool IsWeaponEquip;  // Si tiene el arma equipada
	bool IsWeaponPressed; // Si la animación de equipar/desequipar está en curso
	
	
public:
	// Sets default values for this character's properties
	ATrinitCharacter();

	bool GetIsWeaponEquip() { return IsWeaponEquip; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Delta);
	void MoveRight(float Delta);
	void LookUp(float value);
	void Turn(float value);
	void EquipWeapon();
	void UnequipWeapon();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
