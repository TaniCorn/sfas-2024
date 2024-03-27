#pragma once
#include "Enemy.h"
class IGraphics;
class IShader;
#include <queue>
#include <memory>
class WaveManager
{
public:
	WaveManager();
	WaveManager(IGraphics* Graphics, IShader* Shader, ITexture* FastIn, ITexture* FlyIn, ITexture* SlowIn);
	struct WaveSpawns
	{
		EnemyTypes Type;
		int Amount;
		float TimeToSpawnFromLast;
		int SpawnArea = -1;
	};
	void Update(float DeltaTime);
	void AddNewSpawnArea(DirectX::XMFLOAT2& Area);
	void AddNewSpawn(const EnemyTypes Type, const int Amount, const float TimeToSpawnFromLast, const int Wave, int SpawnArea = -1);

	int WavesLeft() const;
	bool HasWon() const;
	bool CanStartNextWave() const;
	int GetWaveNumber() const;
	const std::vector<Enemy*>& GetAliveEnemies() const;

	void StartNextWave();
	int ProcessEarnedGold();
	 
private:
	int SpawnGroup(const EnemyTypes Type, int Amount, const int Area);
	void SpawnWave();

	std::map<int, std::queue<WaveSpawns>> WaveEntities;
	std::vector<Enemy*> AliveEnemies;

	Enemy EnemyPool[150];
	std::vector<DirectX::XMFLOAT2*> SpawnArea;
	
	int CurrentWave = 0;
	float Timer = 0;
	bool bWaveInProgress = false;
	int GoldGainBuffer = 0;
};

