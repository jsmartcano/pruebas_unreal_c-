// Fill out your copyright notice in the Description page of Project Settings.

#include "Trinit_AnimInstance.h"
#include "Engine.h"
#include "TrinitCharacter.h"

void UTrinit_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UTrinit_AnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{

	Super::NativeUpdateAnimation(DeltaTimeX);

	auto chara = Cast<ATrinitCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (chara) {
		IsInAir = chara->GetMovementComponent()->IsFalling();
		Speed = chara->GetVelocity().Size();
		IsWeaponEquip = chara->GetIsWeaponEquip();
	}
}
