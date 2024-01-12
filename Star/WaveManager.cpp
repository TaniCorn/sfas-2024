#include "WaveManager.h"
#include <list>
#include "Source/Engine/IGraphics.h"
#include "Source/Engine/IShader.h"

WaveManager::WaveManager() : WaveEntities(), SpawnArea(), Fast()
{
}

void WaveManager::Init(IGraphics* Graphics, IShader* Shader, ITexture* FastIn, ITexture* FlyIn, ITexture*SlowIn)
{
	for (int i = 0; i < 50; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(Shader, FastIn, nullptr);
		EnemyPool[i].Init(EnemyRender, Shader, FastPack);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool[i].ColorHighlight.GetColorBind());
		EnemyPool[i].ColorHighlight.Unhighlighted();
		Fast.push(&EnemyPool[i]);
	}
	for (int i = 50; i < 100; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(Shader, FlyIn, nullptr);
		EnemyPool[i].Init(EnemyRender, Shader, Flyers);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool[i].ColorHighlight.GetColorBind());
		EnemyPool[i].ColorHighlight.Unhighlighted();
		Fly.push(&EnemyPool[i]);
	}
	for (int i = 100; i < 150; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(Shader, SlowIn, nullptr);
		EnemyPool[i].Init(EnemyRender, Shader, SlowGrunts);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool[i].ColorHighlight.GetColorBind());
		EnemyPool[i].ColorHighlight.Unhighlighted();
		Slow.push(&EnemyPool[i]);
	}
}

void WaveManager::Update(float DeltaTime)
{
	if (bWaveInProgress)
	{
		Timer -= DeltaTime;
		if (Timer < 0)
		{
			SpawnWave();
		}
	}
	for (int i = 0; i < 150; i++)
	{
		if (EnemyPool[i].IsAlive())
		{
			EnemyPool[i].Update(DeltaTime);

		}
	}
}

void WaveManager::AddNewSpawnArea(DirectX::XMFLOAT2& Area)
{
	SpawnArea.push_back(&Area);
}


void WaveManager::AddNewSpawn(EnemyTypes Type, int Amount, float TimeToSpawnFromLast, int Wave, int SpawnAreaID)
{
	WaveSpawns WaveParam;
	WaveParam.Amount = Amount;
	WaveParam.Type = Type;
	WaveParam.TimeToSpawnFromLast = TimeToSpawnFromLast;
	if (SpawnAreaID == -1)
	{
		int RandomArea = rand() % SpawnArea.size();
		SpawnAreaID = RandomArea;
	}
	WaveParam.SpawnArea = SpawnAreaID;
	WaveEntities[Wave].push(WaveParam);
}

void WaveManager::StartNextWave()
{
	bWaveInProgress = true;
	CurrentWave++;
	Timer = WaveEntities[CurrentWave].front().TimeToSpawnFromLast;
}

bool WaveManager::HasWon()
{
	if (WaveEntities.size() <= 0)
	{
		for (int i = 0; i < 150; i++)
		{
			if (EnemyPool[i].IsAlive()) 
			{
				return false;
			}
		}
		return true;
	}
}

bool WaveManager::CanStartNextWave()
{
	return !bWaveInProgress;
}

int WaveManager::SpawnGroup(std::queue<Enemy*>* Enemies, int Amount, int Area)
{
	int AmountSuccessfullySpawned = 0;
	DirectX::XMFLOAT2 Spawn = *SpawnArea[Area];
	for (int i = 0; i < Amount; i++)
	{
		Enemy* CurrentEnemy = Enemies->front();
		if (CurrentEnemy->IsAlive())
		{
			return AmountSuccessfullySpawned;
		}

		float DeviationX = (rand() % 100) - 50;
		float DeviationY = (rand() % 100) - 50;
		CurrentEnemy->Spawn(DirectX::XMFLOAT2(Spawn.x + DeviationX, Spawn.y + DeviationY));
		AmountSuccessfullySpawned++;
		//Push newly spawned enemy to the back, it is least likely to be dead
		Enemies->pop();
		Enemies->push(CurrentEnemy);
	}
	return AmountSuccessfullySpawned;



}

void WaveManager::SpawnWave()
{
	if (WaveEntities[CurrentWave].size() <= 0)
	{
		//Only the user can start the next wave
		bWaveInProgress = false;
		return;
	}
	int Spawned = 0;
	WaveSpawns Wave = WaveEntities[CurrentWave].front();
	switch (Wave.Type)
	{
	case FastPack:
		Spawned = SpawnGroup(&Fast, Wave.Amount, Wave.SpawnArea);
		break;
	case SlowGrunts:
		Spawned = SpawnGroup(&Slow, Wave.Amount, Wave.SpawnArea);
		break;
	case Flyers:
		Spawned = SpawnGroup(&Fly, Wave.Amount, Wave.SpawnArea);
		break;
	default:
		break;
	}


	if (Spawned == Wave.Amount)
	{
		WaveEntities[CurrentWave].pop();
		Timer = Wave.TimeToSpawnFromLast;
	}
	else 
	{
		WaveEntities[CurrentWave].front().Amount -= Spawned;
		Timer = 0.5f;//Delay before trying to spawn the rest of the enemies
	}
}
