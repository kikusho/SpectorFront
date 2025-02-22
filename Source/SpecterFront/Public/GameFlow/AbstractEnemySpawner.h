﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "SpawnableInterface.h"
#include "ActorContainer.h"
#include "AbstractEnemySpawner.generated.h"

// 敵の生成が終了したことを通知する
DECLARE_DYNAMIC_DELEGATE(FFinishSpawnDelegate);

// 引数構造体
USTRUCT(BlueprintType)
struct FFinishSpawn
{
	GENERATED_BODY()

public:
	// 省略したいデリゲート
	UPROPERTY(BlueprintReadWrite)
		FFinishSpawnDelegate finishSpawnDelegate;

	FFinishSpawn()
		: finishSpawnDelegate()
	{
	}
};

UCLASS(abstract)
class SPECTERFRONT_API AAbstractEnemySpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbstractEnemySpawner();

	virtual void BeginPlay() override;

	// スポーンを開始する
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemySpawner")
		void TriggerSpawn(AAbstractEnemySpawner* parent, FFinishSpawn callback, UActorContainer* allEnemies);

	// 生成した敵の数を取得
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "EnemySpawner")
		int32 GetSpawnedEnemyCount() const;

	// 現在出現中の敵
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "EnemySpawner")
		class UActorContainer* GetAllEnemies() const { return allEnemies; }

	// カメラコントロールクラスを返す
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
		TSubclassOf<class UBaseCameraController> GetCameraControllClass() const { return cameraControllClass; }

	// このターゲットが終了したら自分も終了する
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = "EnemySpawner")
		AActor* seeTargetFinish;

protected:
	// 生成した敵が死亡したときに呼び出される
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn", meta = (BlueprintProtected))
		void OnEnemyDie(TScriptInterface<IEnemyInterface>& enemy);

	// Spawnerの制御を終了
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
		void Finish();

	// スポーン終了を宣言
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
		void EndSpawn();

	// 初期化を行う
	UFUNCTION(BlueprintImplementableEvent, Category = "EnemySpawner", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void Initialize();

	// スポーン開始時に呼ばれる
	UFUNCTION(BlueprintImplementableEvent, Category = "EnemySpawner", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void BeginSpawn();

	// スポーン終了時に呼ばれる
	UFUNCTION(BlueprintImplementableEvent, Category = "EnemySpawner", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void OnEndSpawn();

	// 敵の追加を子から親へ通知
	void NotifiAddEnemy(TScriptInterface<IEnemyInterface> enemy);

	// 敵の消滅を子から親へ通知
	void NotifiRemoveEnemy(TScriptInterface<IEnemyInterface> enemy);

	// シーン上に存在するすべての敵
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		class UActorContainer* allEnemies;

	// 親スポーナー
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		AAbstractEnemySpawner* parent;

	// 自身が管理する敵
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		TArray<TScriptInterface<IEnemyInterface>> spawnedEnemies;

	// 全滅させることで強制的に先へ進む
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
		bool IsAnnihilationFinish;

private:
	// スポーン中、このフラグがtrueの間は、TriggerSpawnを呼ばれてもスポーンが行われない
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		bool isSpawning;

	// 生成中、このフラグがtrueの間は、生成中の敵をすべて倒されても終了しない
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		bool isGenerating;

	// 開始時に自動で一度起動する
	UPROPERTY(EditAnywhere)
		bool isAutoTriggerSpawn;

	// スポーン終了を通知する
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		FFinishSpawn finishSpawnHandler;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UBaseCameraController> cameraControllClass;

	// 管理中の敵の数
	int32 managedEnemyCount;
};
