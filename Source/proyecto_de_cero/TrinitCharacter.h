// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TrinitCharacter.generated.h"

UCLASS()
class PROYECTO_DE_CERO_API ATrinitCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Trinit")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Trinit")
	class UCameraComponent* Camera;
	/*UPROPERTY(VisibleAnywhere, Category = "Trinit")
	UStaticMeshComponent* Mesh2;
*/
public:
	// Sets default values for this character's properties
	ATrinitCharacter();

	UFUNCTION()
		void OnOverlap(class UPrimitiveComponent *OverlappedComponent,
			AActor* OtherActor,
			class   UPrimitiveComponent *OtherComp,
			int32	OtherBodyIndex,
			bool	bFromSweep,
			const	FHitResult &SweepResult);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Delta);
	void MoveRight(float Delta);
	void LookUp(float value);
	void Turn(float value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
