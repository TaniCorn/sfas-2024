#include "GameLevel.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "../../Engine/Implementation/InputSelection.h"
#include "../UI/TextButton.h"
#include "../../Engine/IText.h"

#include "../Towers/AreaTower.h"
#include "../Towers/GroundAreaTower.h"

GameLevel::GameLevel(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = GameLevel1;
}

GameLevel::~GameLevel()
{
	delete ButtonSelector;
}

bool GameLevel::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY = Graphics->GetWindowHeight();
	bool bSuccess = true;
	bSuccess = LoadArea();
	if (!bSuccess)
	{
		return bSuccess;
	}
	bSuccess = LoadUI(screenX, screenY);
	if (!bSuccess)
	{
		return bSuccess;
	}
	bSuccess = LoadEntities();
	if (!bSuccess)
	{
		return bSuccess;
	}
	bSuccess = LoadWaves();
	if (!bSuccess)
	{
		return bSuccess;
	}
	bSuccess = LoadUILinks();
	if (!bSuccess)
	{
		return bSuccess;
	}
	CurrentSelector = ButtonSelector;
	Enemy::TargetPosition = Base->Position;
	Enemy::Target = &Base->Health;
    return true;
}

void GameLevel::Update(float DeltaTime)
{
	RingGamepadSelection->Update(DeltaTime, Input);
	CurrentSelector->Update(Input);

	if (!bPaused)
	{

		Base->Update(DeltaTime);
		Wave.Update(DeltaTime);

		if (Wave.CanStartNextWave())
		{
			StartNextWaveButton->Register(Graphics);
		}
		else
		{
			StartNextWaveButton->Unregister(Graphics);
		}
		for (auto it = CurrencyShop->TowersCreated.begin(); it != CurrencyShop->TowersCreated.end(); it++)
		{
			it._Ptr->_Myval->Update(DeltaTime);
			it._Ptr->_Myval->AttackUpdate(Wave.GetAliveEnemies());
		}

		if (Base->Health.Health <= 0)
		{
			//Lose Game
			//Popup quit/retry UI
			CurrentSelector = EndSelector;
			EndButton->Register(Graphics);
			EndText->SetText("You Lose!");
			Graphics->AddText(EndText);
			bPaused = true;
		}

		if (Wave.HasWon())
		{
			//End Game
			//Popup win UI
			CurrentSelector = EndSelector;
			EndButton->Register(Graphics);
			EndText->SetText("You Win!");
			Graphics->AddText(EndText);
			bPaused = true;
		}
	}

	int Round = Wave.GetWaveNumber();
	RoundString = "Wave: " + std::to_string(Round);
	RoundIndicator->SetText(RoundString.c_str());
	int Currency = CurrencyShop->GetCurrentGold();
	CurrencyString = "Gold: " + std::to_string(Currency);
	CurrencyIndicator->SetText(CurrencyString.c_str());
	int Health = Base->Health.Health;
	HealthString = "Health: " + std::to_string(Health);
	HealthIndicator->SetText(HealthString.c_str());
}

void GameLevel::Cleanup()
{
	Graphics->Cleanup();
}

void GameLevel::StartNextWave()
{
	if (Wave.CanStartNextWave())
	{
		Wave.StartNextWave();
	}
}

bool GameLevel::LoadArea()
{
	int XBound = 400;
	int YBound = 400;

	SpawnAreas[0] = DirectX::XMFLOAT2(-XBound, 0);
	SpawnAreas[1] = DirectX::XMFLOAT2(-XBound, YBound);
	SpawnAreas[2] = DirectX::XMFLOAT2(0, YBound);
	SpawnAreas[3] = DirectX::XMFLOAT2(XBound, YBound);
	SpawnAreas[4] = DirectX::XMFLOAT2(XBound, 0);
	SpawnAreas[5] = DirectX::XMFLOAT2(XBound, -YBound);
	SpawnAreas[6] = DirectX::XMFLOAT2(0, -YBound);
	SpawnAreas[7] = DirectX::XMFLOAT2(-XBound, -YBound);
	return true;
}

bool GameLevel::LoadEntities()
{
	IShader* ColorChangeShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");

	ITexture* BaseTexture = Graphics->CreateTexture(L"Resource/Textures/Base.png", "Base");
	IRenderable* BaseRender = Graphics->CreateFloat4Billboard(ColorChangeShader, BaseTexture, nullptr);
	Base = new HomeBase(BaseRender, ColorChangeShader);
	Base->Register(Graphics);
	

	ITexture* RingTextureInner = Graphics->CreateTexture(L"Resource/Textures/InnerRing.dds", "InnerRing");
	ITexture* RingTextureMiddle = Graphics->CreateTexture(L"Resource/Textures/MiddleRing.dds", "MiddleRing");
	ITexture* RingTextureOuter = Graphics->CreateTexture(L"Resource/Textures/OuterRing.dds", "OuterRing");
	IRenderable* InnerRing = Graphics->CreateFloat4Billboard(ColorChangeShader, RingTextureInner, nullptr);
	IRenderable* MiddleRing = Graphics->CreateFloat4Billboard(ColorChangeShader, RingTextureMiddle, nullptr);
	IRenderable* OuterRing = Graphics->CreateFloat4Billboard(ColorChangeShader, RingTextureOuter, nullptr);
	Rings[0] = new DefenceRing(ColorChangeShader, InnerRing);
	Rings[1] = new DefenceRing(ColorChangeShader, MiddleRing);
	Rings[2] = new DefenceRing(ColorChangeShader, OuterRing);
	for (int i = 0; i < 3; i++)
	{
		Rings[i]->Register(Graphics);
	}

	for (int i = 0; i < 3; i++)
	{
		IRenderable* Plot = Graphics->CreateFloat4Billboard(ColorChangeShader, BaseTexture, nullptr);
		Plots[i] = new TowerPlot(ColorChangeShader, Plot);
		Plots[i]->Register(Graphics);
		//Todo after getting the art assets
		Plots[i]->SetScale(0.5, 0.5);
		float Pos = 55 * (i+1);
		Plots[i]->SetPosition(DirectX::XMFLOAT2(0, Pos));
		Plots[i]->DistanceFromCenter = Pos;
		Plots[i]->Rotation = 0;
	}

	Rings[0]->Plots.push_back(Plots[0]);
	Rings[1]->Plots.push_back(Plots[1]);
	Rings[2]->Plots.push_back(Plots[2]);


	ITexture* AreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/Tower.png", "AreaTower");
	IRenderable* AreaTowerRemderable = Graphics->CreateFloat4Billboard(ColorChangeShader, AreaTowerTexture, nullptr);
	TowerClones[0] = new AreaTower(ColorChangeShader, AreaTowerRemderable);
	ITexture* GroundAreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/GroundTower.png", "GroundAreaTower");
	IRenderable* GroundAreaTowerRenderable = Graphics->CreateFloat4Billboard(ColorChangeShader, AreaTowerTexture, nullptr);
	TowerClones[1] = new GroundAreaTower(ColorChangeShader, GroundAreaTowerRenderable);
	CurrencyShop = new Shop(100);
	ITexture* EnemyPackTextures = Graphics->CreateTexture(L"Resource/Textures/Fast.png", "EnemyPack");
	ITexture* EnemyFlyTextures = Graphics->CreateTexture(L"Resource/Textures/Fly.png", "EnemyFly");
	ITexture* EnemySlowTextures = Graphics->CreateTexture(L"Resource/Textures/Slow.png", "EnemySlow");
	Wave.Init(Graphics, ColorChangeShader, EnemyPackTextures, EnemyFlyTextures, EnemySlowTextures);
	for (int i = 0; i < 8; i++)
	{
		Wave.AddNewSpawnArea(SpawnAreas[i]);
	}
	Wave.ShopReference = CurrencyShop;
	return true;
}

bool GameLevel::LoadWaves()
{
	int WaveNumber = 1;
	//Wave 1
	Wave.AddNewSpawn(SlowGrunts, 2, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 5, 5, WaveNumber);
	Wave.AddNewSpawn(FastPack, 5, 5, WaveNumber);
	WaveNumber++;
	//Wave 3
	Wave.AddNewSpawn(FastPack, 5, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 15, 10, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 3, 5, WaveNumber);
	WaveNumber++;
	//Wave 3
	Wave.AddNewSpawn(Flyers, 5, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 10, 10, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 5, 0, WaveNumber);
	WaveNumber++;
	//Wave 4
	Wave.AddNewSpawn(FastPack, 10, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 10, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 10, 0, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 5, 5, WaveNumber);
	WaveNumber++;
	//Wave 5
	Wave.AddNewSpawn(FastPack, 10, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 5, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 10, 5, WaveNumber);
	WaveNumber++;
	//Wave 6
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 10, 5, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 10, 0, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 10, 0, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 10, 0, WaveNumber);
	WaveNumber++;
	//Wave 7
	Wave.AddNewSpawn(FastPack, 15, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 15, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 5, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(SlowGrunts, 10, 5, WaveNumber);
	Wave.AddNewSpawn(FastPack, 20, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 20, 0, WaveNumber);
	Wave.AddNewSpawn(FastPack, 20, 0, WaveNumber);
	WaveNumber++;

	return true;
}

bool GameLevel::LoadUI(float screenX, float screenY)
{
	IShader* ButtonShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	ITexture* ButtonTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");
	IRenderable* StartRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* StartText = Graphics->CreateText("Start Next Wave", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	StartNextWaveButton = new TextButton(StartRender, StartText, ButtonShader, screenX, screenY);
	StartNextWaveButton->SetPosition(-700, -300);
	StartNextWaveButton->SetButtonScale(4, 2);
	StartNextWaveButton->AddTextPosition(-200, 25);
	StartNextWaveButton->Register(Graphics);
	StartNextWaveButton->Interact.BoundFunction = std::bind(&GameLevel::StartNextWave, this);
	IRenderable* OpenRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* OpenText = Graphics->CreateText("Open Shop", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	OpenShopButton = new TextButton(OpenRender, OpenText, ButtonShader, screenX, screenY);
	OpenShopButton->SetPosition(0, -300);
	OpenShopButton->SetButtonScale(4, 2);
	OpenShopButton->AddTextPosition(-200, 25);
	OpenShopButton->Register(Graphics);
	OpenShopButton->Interact.BoundFunction = std::bind(&GameLevel::OpenShop, this);
	IRenderable* QuitRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* QuitText = Graphics->CreateText("Quit Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	QuitButton = new TextButton(QuitRender, QuitText, ButtonShader, screenX, screenY);
	QuitButton->SetPosition(700, -300);
	QuitButton->SetButtonScale(4, 2);
	QuitButton->AddTextPosition(-200, 25);
	QuitButton->Register(Graphics);
	QuitButton->Interact.BoundFunction = std::bind(&GameLevel::QuitGame, this);
	IRenderable* EndRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* EndButtonText = Graphics->CreateText("End Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	EndButton = new TextButton(EndRender, EndButtonText, ButtonShader, screenX, screenY);
	EndButton->SetPosition(0, 200);
	EndButton->SetButtonScale(4, 2);
	EndButton->AddTextPosition(-200, 25);
	EndButton->Register(Graphics);
	EndButton->Unregister(Graphics);
	EndText = Graphics->CreateText("END CONDITION", (screenX / 2) - 200, 50);
	EndButton->Interact.BoundFunction = std::bind(&GameLevel::QuitGame, this);
	Graphics->AddText(EndText);
	Graphics->RemoveText(EndText);

	RoundIndicator = Graphics->CreateText("Round: X");
	CurrencyIndicator = Graphics->CreateText("Gold: X", 0, 50);
	HealthIndicator = Graphics->CreateText("Health: X", 0, 100);
	Graphics->AddText(RoundIndicator);
	Graphics->AddText(CurrencyIndicator);
	Graphics->AddText(HealthIndicator);

	IText* AreaTowerText = Graphics->CreateText("60 Gold", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	ITexture* AreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");
	IRenderable* AreaTowerRenderable = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	TowerButtons[0] = new TextButton(AreaTowerRenderable, AreaTowerText, ButtonShader, screenX, screenY);
	TowerButtons[0]->SetPosition(-300, 0);
	TowerButtons[0]->SetButtonScale(2, 2);
	TowerButtons[0]->AddTextPosition(-200, 25);
	TowerButtons[0]->Register(Graphics);
	TowerButtons[0]->Unregister(Graphics);
	TowerButtons[0]->Interact.BoundFunction = std::bind(&GameLevel::SpawnAreaTower, this);
	IText* GroundAreaTowerText = Graphics->CreateText("40 Gold", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	ITexture* GroundAreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");
	IRenderable* GroundAreaTowerRenderable = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	TowerButtons[1] = new TextButton(GroundAreaTowerRenderable, GroundAreaTowerText, ButtonShader, screenX, screenY);
	TowerButtons[1]->SetPosition(300, 0);
	TowerButtons[1]->SetButtonScale(2, 2);
	TowerButtons[1]->AddTextPosition(-200, 25);
	TowerButtons[1]->Register(Graphics);
	TowerButtons[1]->Unregister(Graphics);
	TowerButtons[1]->Interact.BoundFunction = std::bind(&GameLevel::SpawnGroundAreaTower, this);
	return true;
}

bool GameLevel::LoadUILinks()
{
	ButtonSelector = new InputSelection(&StartNextWaveButton->Interact);
	ButtonSelector->AddButtonLink(&StartNextWaveButton->Interact, &OpenShopButton->Interact, Right);
	ButtonSelector->AddButtonLink(&OpenShopButton->Interact, &StartNextWaveButton->Interact, Left);
	ButtonSelector->AddButtonLink(&OpenShopButton->Interact, &QuitButton->Interact, Right);
	ButtonSelector->AddButtonLink(&QuitButton->Interact, &OpenShopButton->Interact, Left);

	RingGamepadSelection = new RingSelection(Rings[0]);
	RingGamepadSelection->AddLink(Rings[0], Rings[1], true);
	RingGamepadSelection->AddLink(Rings[1], Rings[0], false);
	RingGamepadSelection->AddLink(Rings[1], Rings[2], true);
	RingGamepadSelection->AddLink(Rings[2], Rings[1], false);

	ShopSelector = new InputSelection(&TowerButtons[0]->Interact);
	ShopSelector->AddButtonLink(&TowerButtons[0]->Interact, &TowerButtons[1]->Interact, Right);
	ShopSelector->AddButtonLink(&TowerButtons[1]->Interact, &TowerButtons[0]->Interact, Left);
	ShopSelector->PreviousMenuFunction = std::bind(&GameLevel::CloseShop, this);

	EndSelector = new InputSelection(&EndButton->Interact);
	return true;
}

void GameLevel::OpenShop()
{
	CurrentSelector = ShopSelector;
	bPaused = true;
	TowerButtons[0]->Register(Graphics);
	TowerButtons[1]->Register(Graphics);

}

void GameLevel::CloseShop()
{
	CurrentSelector = ButtonSelector;
	bPaused = false;
	TowerButtons[0]->Unregister(Graphics);
	TowerButtons[1]->Unregister(Graphics);
}

void GameLevel::SpawnAreaTower()
{
	if (CurrencyShop->CanPurchase(TowerClones[0]->GetCost()))
	{
		for (int i = 0; i < 3; i++)
		{
			if (Rings[i]->PlotAvailable())
			{
				Tower* TowerIn = CurrencyShop->CreateTower(TowerClones[0], Graphics);
				Rings[i]->PlantTower(TowerIn);
				CurrencyShop->Spend(TowerIn->GetCost());
				return;
			}
		}
	}
}

void GameLevel::SpawnGroundAreaTower()
{
	if (CurrencyShop->CanPurchase(TowerClones[1]->GetCost()))
	{
		for (int i = 0; i < 3; i++)
		{
			if (Rings[i]->PlotAvailable())
			{
				Tower* TowerIn = CurrencyShop->CreateTower(TowerClones[1], Graphics);
				Rings[i]->PlantTower(TowerIn);
				CurrencyShop->Spend(TowerIn->GetCost());
				return;
			}
		}
	}
}

void GameLevel::QuitGame()
{
	LevelSwitchKey = MainMenuLevel;
}
