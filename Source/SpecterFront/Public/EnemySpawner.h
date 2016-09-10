// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "BaseEnemy.h"
#include "EnemySpawner.generated.h"

// �G�̐������I���������Ƃ�ʒm����
DECLARE_DYNAMIC_DELEGATE(FCompleteDelegate);

/**
 * �G�̏o���ʒu���w�肷�邽�߂̃I�u�W�F�N�g
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API AEnemySpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	// �����B�u���[�v�����g���ŃI�[�o�[���C�h����ꍇ�̓I�[�o�[���C�h�����ĂԂ���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Spawn(AEnemySpawnController* spawnController);

public:
	// �X�|�[�����Ǘ�����I�u�W�F�N�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AEnemySpawnController* spawnController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABaseEnemy> spawnEnemy;

	//UPROPERTY(BlueprintReadWrite)
	//	FCompleteDelegate completeEvent;

public:
	// ���݂̃X�|�[�i�[���琧����ڂ��ۂɌĂяo��
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void Complete();
};
