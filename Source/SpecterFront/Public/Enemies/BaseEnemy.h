// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Character.h"
#include "DamageListenerInterface.h"
#include "EnemyInterface.h"
#include "BaseEnemy.generated.h"

// 敵が死亡したときに通知する
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifiEnemyDieDelegate, class TScriptInterface<IEnemyInterface>, enemy);
UCLASS(abstract, Blueprintable, BlueprintType)
class SPECTERFRONT_API ABaseEnemy : public APawn, public IDamageListenerInterface, public IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void Wait(float tick);
	//IEnemyInterfaceの実装
	// 死亡時に通知する先を登録
	// 死亡時にobserverに含まれるOnEnemyDie()を呼び出す
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void AddObserver(UObject* observer);
	virtual void AddObserver_Implementation(UObject* observer) override;

	//IEnemyInterfaceの実装
	// 通知先を削除
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void RemoveObserver(UObject* observer);
	virtual void RemoveObserver_Implementation(UObject* observer) override;
public: // UFUNCTION
	
	// HP
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE float GetMaxHp() const { return maxHp; }
	// HP
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE float GetHp() const { return hp; }
	// Score
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE int32 GetScore() const { return score; }
	// 攻撃力
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE float GetPower() const { return power; }

	// 死亡済みか
	UFUNCTION(BlueprintCallable, Category = "Character")
		bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character", meta = (BlueprintProtected))
		void OnDeath(AController* instigatedBy, AActor* damageCauser);

	// IDamageListenerInterfaceの実装
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	//IEnemyInterfaceの実装
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void MoveTo();

	//IEnemyInterfaceの実装
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void Appearance();

	// 殺す
	UFUNCTION(BlueprintCallable, Category = "Character")
		void Kill(AController* instigatedBy, AActor* damageCauser);

	// 死亡時に通知する
	UPROPERTY(BlueprintAssignable)
		FNotifiEnemyDieDelegate notifiEnemyDieEventDispather;
private: // UPROPERTY
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float hp;
	// Score
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		int32 score;
	// 攻撃力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float power;
	// 最大HP
	UPROPERTY(BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float maxHp;

	
};
