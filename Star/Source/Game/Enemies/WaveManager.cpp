#include "WaveManager.h"
#include <list>
#include "../Source/Engine/IGraphics.h"
#include "../Source/Engine/IShader.h"
WaveManager::WaveManager(IGraphics* Graphics, IShader* Shader, ITexture* FastIn, ITexture* FlyIn, ITexture* SlowIn) : WaveEntities(), SpawnArea()
{
	for (int i = 0; i < 50; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(Shader, FastIn, nullptr);
		EnemyPool[i] = Enemy(EnemyRender, Shader, EnemyTypes::FastPacks);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool[i].ColorHighlight.GetColorBind());
		EnemyPool[i].ColorHighlight.SetHighlightColor(0.5, 0, 0, 0.3);
		EnemyPool[i].ColorHighlight.SetNormalColor(0, 0, 0, 0);
		EnemyPool[i].ColorHighlight.Unhighlighted();
	}
	for (int i = 50; i < 100; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(Shader, FlyIn, nullptr);
		EnemyPool[i] = Enemy(EnemyRender, Shader, EnemyTypes::Flyers);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool[i].ColorHighlight.GetColorBind());
		EnemyPool[i].ColorHighlight.SetHighlightColor(0.5, 0, 0, 0.3);
		EnemyPool[i].ColorHighlight.SetNormalColor(0, 0, 0, 0);
		EnemyPool[i].ColorHighlight.Unhighlighted();
	}
	for (int i = 100; i < 150; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(Shader, SlowIn, nullptr);
		EnemyPool[i] = Enemy(EnemyRender, Shader, EnemyTypes::SlowGrunts);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool[i].ColorHighlight.GetColorBind());
		EnemyPool[i].ColorHighlight.SetHighlightColor(0.5, 0, 0, 0.3);
		EnemyPool[i].ColorHighlight.SetNormalColor(0, 0, 0, 0);
		EnemyPool[i].ColorHighlight.Unhighlighted();
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
	for (int i = 0; i < AliveEnemies.size(); i++)
	{
		
		if (AliveEnemies[i])
		{
			AliveEnemies[i]->Update(DeltaTime);
		}
		if (!AliveEnemies[i]->IsAlive())
		{
			GoldGainBuffer += AliveEnemies[i]->GetGoldGain();
			AliveEnemies.erase(AliveEnemies.begin() + i);
		}
	}
	AliveEnemies.shrink_to_fit();

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
	WaveEntities.erase(CurrentWave);
	bWaveInProgress = true;
	CurrentWave++;
	Timer = WaveEntities[CurrentWave].front().TimeToSpawnFromLast;
}

int WaveManager::GetWaveNumber() const
{
	return CurrentWave;
}

int WaveManager::ProcessEarnedGold()
{
	int Gold = GoldGainBuffer;
	GoldGainBuffer = 0;
	return Gold;
}

const std::vector<Enemy*>& WaveManager::GetAliveEnemies() const
{
	return AliveEnemies;
}

int WaveManager::WavesLeft() const
{
	return WaveEntities.size();
}

bool WaveManager::HasWon() const
{
	if (WaveEntities.size() <= 1)
	{
		if (AliveEnemies.size() <= 0)
		{
			return true;
		}
	}
	return false;
}

bool WaveManager::CanStartNextWave() const
{
	return !bWaveInProgress;
}

int WaveManager::SpawnGroup(EnemyTypes Type, int Amount, int Area)
{
	int Range = 50;
	switch (Type)
	{
	case EnemyTypes::FastPacks:
		Range = 50;
		break;
	case EnemyTypes::Flyers:
		Range = 100;
		break;
	case EnemyTypes::SlowGrunts:
		Range = 150;
		break;
	default:
		break;
	}

	DirectX::XMFLOAT2 Spawn = *SpawnArea[Area];
	int AmountSuccessfullySpawned = 0;
	//Spawn enemy
	for (int i = Range-50; i < Range; i++)
	{
		if (AmountSuccessfullySpawned >= Amount)
		{
			return AmountSuccessfullySpawned;
		}
		Enemy* CurrentEnemy = &EnemyPool[i];
		if (CurrentEnemy->IsAlive())
		{
			continue;
		}

		float DeviationX = (rand() % 400) - 200;
		float DeviationY = (rand() % 400) - 200;
		CurrentEnemy->Spawn(DirectX::XMFLOAT2(Spawn.x + DeviationX, Spawn.y + DeviationY));
		AliveEnemies.push_back(CurrentEnemy);
		AmountSuccessfullySpawned++;

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
	Spawned = SpawnGroup(Wave.Type, Wave.Amount, Wave.SpawnArea);

	if (Spawned >= Wave.Amount)
	{
		Timer = Wave.TimeToSpawnFromLast;
		WaveEntities[CurrentWave].pop();
	}
	else 
	{
		WaveEntities[CurrentWave].front().Amount -= Spawned;
		Timer = 0.5f;//Delay before trying to spawn the rest of the enemies
	}
}
