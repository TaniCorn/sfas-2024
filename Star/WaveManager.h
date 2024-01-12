#pragma once
#include "Source/Game/Enemies/Enemy.h"
class IGraphics;
class IShader;
#include <queue>
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

	bool HasWon();
	bool CanStartNextWave();
	void StartNextWave();
private:
	int SpawnGroup(std::queue<Enemy*>* Enemies, int Amount, int Area);
	void SpawnWave();
	std::map<int, std::queue<WaveSpawns>> WaveEntities;
	std::queue<Enemy*> Fast;
	std::queue<Enemy*> Slow;
	std::queue<Enemy*> Fly;
	Enemy EnemyPool[150];
	std::vector<DirectX::XMFLOAT2*> SpawnArea;

	int CurrentWave = 0;
	float Timer = 0;
	bool bWaveInProgress = false;
};

