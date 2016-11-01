// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "ActionPhaseController.generated.h"

UCLASS()
class SPECTERFRONT_API AActionPhaseController : public AEnemySpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActionPhaseController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public: // UFUNCTION
	// �A�N�V�����t�F�[�Y�I�����ɌĂяo��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Finish();

	// �X�|�[�������G��ActionPhase�̊Ǘ����ɒu��
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AppendSpawnEnemies(const TArray<class ABaseEnemy*>& enemies);
	// �X�|�[�������G��ActionPhase�̊Ǘ����ɒu��
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AddSpawnEnemy(class ABaseEnemy* enemy);

	// ���������G�����S�����Ƃ��ɌĂяo�����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn", meta = (BlueprintProtected))
		void OnEnemyDie(class ABaseEnemy* enemy);

public: // UPROPERTY
	UPROPERTY(BlueprintReadOnly, Category = "EnemySpawn", meta = (BlueprintProtected))
		TArray<class ABaseEnemy*> managedEnemies;
};
