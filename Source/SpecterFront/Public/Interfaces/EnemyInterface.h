// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyInterface.generated.h"


UINTERFACE(BlueprintType)
class UEnemyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// すべての敵はこれを実装する
class IEnemyInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void MoveTo();

	// 出現時に呼ぶ
	UFUNCTION(BlueprintImplementableEvent)
		void Appearance();

	// 死亡時に通知する先を登録
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void AddObserver(UObject* observer);

	// 通知先を削除
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void RemoveObserver(UObject* observer);
};