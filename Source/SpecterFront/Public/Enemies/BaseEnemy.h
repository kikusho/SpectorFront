// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DamageListenerInterface.h"
#include "EnemyInterface.h"
#include "BaseEnemy.generated.h"

// �G�����S�����Ƃ��ɒʒm����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifiEnemyDieDelegate, class TScriptInterface<IEnemyInterface>, enemy);

UCLASS(abstract, Blueprintable, BlueprintType)
class SPECTERFRONT_API ABaseEnemy : public APawn, public IDamageListenerInterface, public IEnemyInterface
{
	GENERATED_BODY()

public:

	virtual void Wait(float tick);

	//IEnemyInterface�̎���
	// ���S���ɒʒm������o�^
	// ���S����observer�Ɋ܂܂��OnEnemyDie()���Ăяo��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void AddObserver(UObject* observer);
		virtual void AddObserver_Implementation(UObject* observer) override;

	//IEnemyInterface�̎���
	// �ʒm����폜
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void RemoveObserver(UObject* observer);
		virtual void RemoveObserver_Implementation(UObject* observer) override;

public: // UFUNCTION

	// ���S�ς݂�
	UFUNCTION(BlueprintCallable, Category = "Character")
		bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character", meta = (BlueprintProtected))
		void OnDeath(AController* instigatedBy, AActor* damageCauser);

	// IDamageListenerInterface�̎���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	//IEnemyInterface�̎���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void MoveTo();

	//IEnemyInterface�̎���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void Appearance();

	// �E��
	UFUNCTION(BlueprintCallable, Category = "Character")
		void Kill(AController * instigatedBy, AActor * damageCauser);

private: // UPROPERTY
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float hp;
	// Score
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		int32 score;
	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float power;

	// ���S���ɒʒm����
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
		FNotifiEnemyDieDelegate notifiEnemyDieEventDispather;
};
