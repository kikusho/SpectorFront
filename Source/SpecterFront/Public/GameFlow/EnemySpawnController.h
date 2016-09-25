// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.generated.h"


UCLASS()
class SPECTERFRONT_API AEnemySpawnController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public: // UFUNCTION
	// �G�̐���������J�n����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void BeginSpawnSequence(const FFinishSpawnDelegate& finishEvent);

	// �����I����ʒm����
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void FinishSpawnSequence();

	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void OnEnemyDie(class ABaseEnemy* enemy);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void OnFinishSpawn();

	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AddSpawnEnemy(ABaseEnemy* spawnEnemy);

public: // UPROPERTY
	UPROPERTY(BlueprintReadOnly, Meta = (ExposeOnSpawn = true))
		TArray<class AEnemySpawner*> spawnerList;

	UPROPERTY(BlueprintReadOnly)
		TArray<ABaseEnemy*> spawnEnemies;

private:
	FFinishSpawnDelegate completeHandler;
};
