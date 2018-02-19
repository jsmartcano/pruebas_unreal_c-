// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Trinit_AnimInstance.generated.h"

/**
 *  Se crea esta clase, y es importante, hacer un REPARENT del blueprint
 de Animación, o de crear uno nuevo directamente de esta
 */
UCLASS()
class PROYECTO_DE_CERO_API UTrinit_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()




public:

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category="Trinit")
	float Speed;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Trinit")
	bool IsInAir;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	
	
};
