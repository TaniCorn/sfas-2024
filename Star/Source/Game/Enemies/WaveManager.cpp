#include "WaveManager.h"
#include <list>
#include "../Source/Engine/IGraphics.h"
#include "../Source/Engine/IShader.h"
WaveManager::WaveManager() : WaveEntities(), SpawnArea()
{
}

void WaveManager::Init(IGraphics* Graphics, IShader* Shader, ITexture* FastIn, ITexture* FlyIn, ITexture* SlowIn)
{
	//50 for each enemy
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
	//Spawns the next group of enemies in the round
	if (bWaveInProgress)
	{
		Timer -= DeltaTime;
		if (Timer < 0)
		{
			SpawnWave();
		}
	}
	//Updates enemies, and adds gold to buffer from dead enemies
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
	//Choose a random spawn area
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
	//Remove current wave(empty wave, all enemies have spawned)
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
	//Returns the gold gained this frame
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
	//If there is only 1 wave left(empty after all enemies have spawned), and there are no alive enemies
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

int WaveManager::SpawnGroup(EnemyTypes Type, int AmountToSpawn, int Area)
{
	//Pick from the array range of enemies; 0-50 is fast packs, 50-100 is flyers, 100-150 is slowgrunts.
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

	//Choose spawn location
	DirectX::XMFLOAT2 Spawn = *SpawnArea[Area];
	int AmountSuccessfullySpawned = 0;
	//Spawn enemy
	for (int i = Range-50; i < Range; i++)
	{
		//If not all enemies could be spawned, (because there was not enough in the pool) return how many there is left to spawn
		if (AmountSuccessfullySpawned >= AmountToSpawn)
		{
			return AmountSuccessfullySpawned;
		}
		//Continues to next enemy if current enemy is alive
		Enemy* CurrentEnemy = &EnemyPool[i];
		if (CurrentEnemy->IsAlive())
		{
			continue;
		}

		//Randomness to spawn location so enemies don't stack
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
	//If all enemies in current wave have spawned
	if (WaveEntities[CurrentWave].size() <= 0)
	{
		//Only the user can start the next wave
		bWaveInProgress = false;
		return;
	}

	//Spawn wave
	int Spawned = 0;
	WaveSpawns Wave = WaveEntities[CurrentWave].front();
	Spawned = SpawnGroup(Wave.Type, Wave.Amount, Wave.SpawnArea);

	//Checking whether all enemies successfully spawned
	if (Spawned >= Wave.Amount)
	{
		//Start timer for next wave of enemies inside the round, and remove the wave that just got spawned
		Timer = Wave.TimeToSpawnFromLast;
		WaveEntities[CurrentWave].pop();
	}
	else 
	{
		//Try spawning enemies again
		WaveEntities[CurrentWave].front().Amount -= Spawned;
		Timer = 0.5f;//Delay before trying to spawn the rest of the enemies
	}
}
