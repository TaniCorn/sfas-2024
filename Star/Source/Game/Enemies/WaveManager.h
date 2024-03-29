#pragma once
#include "Enemy.h"
class IGraphics;
class IShader;
#include <queue>
#include <memory>


/// <summary>
/// The wave manager handles the spawning, gold aquisition, and enemies inside a level.
/// Using a round and waves system, Round 1 can have 5 different waves of enemies, and so on
/// </summary>
class WaveManager
{
public:
	struct WaveSpawns
	{
		EnemyTypes Type;
		int Amount;
		float TimeToSpawnFromLast;
		int SpawnArea = -1;
	};
	WaveManager();
	void Init(IGraphics* Graphics, IShader* Shader, ITexture* FastIn, ITexture* FlyIn, ITexture* SlowIn);

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

	//Map of Roundnumbers, and a queue of enemy waves inside the round
	std::map<int, std::queue<WaveSpawns>> WaveEntities;
	//Enemies that have spawned and not been killed
	std::vector<Enemy*> AliveEnemies;

	//Enemy pool of 50 enemies each
	Enemy EnemyPool[150];
	std::vector<DirectX::XMFLOAT2*> SpawnArea;
	
	int CurrentWave = 0;
	float Timer = 0;
	bool bWaveInProgress = false;
	int GoldGainBuffer = 0;
};

