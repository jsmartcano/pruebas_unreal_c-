// Fill out your copyright notice in the Description page of Project Settings.

#include "Trinit_AnimInstance.h"
#include "Engine.h"

void UTrinit_AnimInstance::NativeInitializeAnimation()
{
	

}

void UTrinit_AnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	ACharacter* chara = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (chara) {
		IsInAir = chara->GetMovementComponent()->IsFalling();
		Speed = chara->GetVelocity().Size();
	}
}
