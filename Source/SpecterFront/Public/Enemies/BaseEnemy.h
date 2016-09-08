// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "DamageListenerInterface.h"
#include "BaseEnemy.generated.h"

UCLASS(abstract, Blueprintable, BlueprintType)
class SPECTERFRONT_API ABaseEnemy : public APawn, public IDamageListenerInterface
{
	GENERATED_BODY()

public:
	virtual void Wait(float tick);

	// ���S�ς݂�
	UFUNCTION(BlueprintCallable, Category = "Character")
		bool IsDead() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
		void OnDeath(AController* instigatedBy, AActor* damageCauser);

	// IDamageListenerInterface�̎���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float hp;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float power;
};
