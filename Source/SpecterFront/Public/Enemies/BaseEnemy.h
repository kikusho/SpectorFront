// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DamageListenerInterface.h"
#include "BaseEnemy.generated.h"

// �G�����S�����Ƃ��ɒʒm����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifiEnemyDieDelegate, class ABaseEnemy*, enemy);

UCLASS(abstract, Blueprintable, BlueprintType)
class SPECTERFRONT_API ABaseEnemy : public APawn, public IDamageListenerInterface
{
	GENERATED_BODY()

public:

	virtual void Wait(float tick);

	// ���S���ɒʒm������o�^
	void AddObserver(const FScriptDelegate& observer);

	// �ʒm����폜
	void RemoveObserver(UObject* const observer);

public: // UFUNCTION

	// ���S�ς݂�
	UFUNCTION(BlueprintCallable, Category = "Character")
		bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character", meta = (BlueprintProtected))
		void OnDeath(AController* instigatedBy, AActor* damageCauser);

	// IDamageListenerInterface�̎���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	// �E��
	UFUNCTION(BlueprintCallable, Category = "Character")
		void Kill(AController * instigatedBy, AActor * damageCauser);

private: // UPROPERTY

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float hp;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float power;

	// ���S���ɒʒm����
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
		FNotifiEnemyDieDelegate notifiEnemyDieEventDispather;
};
