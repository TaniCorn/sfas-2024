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
	void Init(IGraphics* Graphics, IShader* Shader, ITexture* Fast, ITexture* Fly, ITexture* Slow);
	struct WaveSpawns
	{
		EnemyTypes Type;
		int Amount;
		float TimeToSpawnFromLast;
		int SpawnArea = -1;
	};
	void Update(float DeltaTime);
	void AddNewSpawnArea(DirectX::XMFLOAT2& Area);
	void AddNewSpawn(EnemyTypes Type, int Amount, float TimeToSpawnFromLast, int Wave, int SpawnArea = -1);

	int WavesLeft();
	bool HasWon();
	bool CanStartNextWave();
	void StartNextWave();
	int GetWaveNumber();
	int ProcessEarnedGold();
	const std::vector<Enemy*>& GetAliveEnemies();
	 
private:
	int SpawnGroup(EnemyTypes Type, int Amount, int Area);
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

