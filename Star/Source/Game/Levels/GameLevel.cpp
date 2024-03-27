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
	LevelSwitchKey = LevelId::GameLevel1;
}

GameLevel::~GameLevel()
{
}

bool GameLevel::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY = Graphics->GetWindowHeight();
	bool bSuccess = true;
	ITexture* BackgroundTexture = Graphics->CreateTexture(L"Resource/Textures/Water.png", "Background");
	IShader* BackgroundShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	IRenderable* BackgroundRender = Graphics->CreateBillboard(BackgroundShader, BackgroundTexture);
	BackgroundRender->SetScale(40, 20);
	Graphics->AddSpriteToRender(BackgroundShader, BackgroundRender, 0);

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
	Enemy::TargetHealthObject = &Base->Health;
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
		CurrencyShop->AddGold(Wave.ProcessEarnedGold());

		if (Wave.CanStartNextWave() && Wave.WavesLeft() > 1)
		{
			StartNextWaveButton->Register(Graphics);
		}
		else
		{
			StartNextWaveButton->Unregister(Graphics);
		}
		for (int i = 0; i < 3; i++)
		{
			Rings[i]->Update(DeltaTime, Wave.GetAliveEnemies());
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
	if (Wave.CanStartNextWave() && Wave.WavesLeft() > 1)
	{
		Wave.StartNextWave();
	}
}

bool GameLevel::LoadArea()
{
	int XBound = 800;
	int YBound = 600;

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
	Base = std::make_unique<HomeBase>(BaseRender, ColorChangeShader);
	Base->Register(Graphics);

	

	ITexture* RingTextureInner = Graphics->CreateTexture(L"Resource/Textures/InnerRing.dds", "InnerRing");
	IRenderable* InnerRing = Graphics->CreateFloat4Billboard(ColorChangeShader, RingTextureInner, nullptr);
	Rings[0] = new DefenceRing(ColorChangeShader, InnerRing);
	Rings[1] = new DefenceRing(ColorChangeShader, InnerRing);
	Rings[2] = new DefenceRing(ColorChangeShader, InnerRing);


	ITexture* PlotTexture = Graphics->CreateTexture(L"Resource/Textures/Plot.png", "Plot");
	for (int i = 0; i < 2; i++)
	{
		IRenderable* PlotRenderable = Graphics->CreateFloat4Billboard(ColorChangeShader, PlotTexture, nullptr);
		std::unique_ptr<TowerPlot> Plot (new TowerPlot(ColorChangeShader, PlotRenderable));
		Plot->Register(Graphics);
		Plot->SetScale(0.5, 0.5);
	

		float DistFromCenter = 150; 
		
		float Rotation = 180 * i; 
		float radRot = Rotation * 3.14159265359f / 180;
		int y = (cos(radRot) * (DistFromCenter));
		int x = (sin(radRot) * (DistFromCenter));
		Plot->SetPosition(DirectX::XMFLOAT2(x, y));
		Plot->Rotation = Rotation;
		Plot->DistanceFromCenter = DistFromCenter;
		Rings[0]->PlantPlot(std::move(Plot));
	}
	for (int i = 2; i < 6; i++)
	{
		IRenderable* PlotRenderable = Graphics->CreateFloat4Billboard(ColorChangeShader, PlotTexture, nullptr);
		std::unique_ptr<TowerPlot> Plot(new TowerPlot(ColorChangeShader, PlotRenderable));
		Plot->Register(Graphics);
		Plot->SetScale(0.5, 0.5);

		float DistFromCenter = 300;

		float Rotation = 90 * i;
		float radRot = Rotation * 3.14159265359f / 180;
		int y = (cos(radRot) * (DistFromCenter));
		int x = (sin(radRot) * (DistFromCenter));
		Plot->SetPosition(DirectX::XMFLOAT2(x, y));
		Plot->Rotation = Rotation;
		Plot->DistanceFromCenter = DistFromCenter;
		Rings[1]->PlantPlot(std::move(Plot));
	}
	for (int i = 6; i < 14; i++)
	{
		IRenderable* PlotRenderable = Graphics->CreateFloat4Billboard(ColorChangeShader, PlotTexture, nullptr);
		std::unique_ptr<TowerPlot> Plot(new TowerPlot(ColorChangeShader, PlotRenderable));
		Plot->Register(Graphics);
		Plot->SetScale(0.5, 0.5);

		float DistFromCenter = 450;

		float Rotation = (360/8) * i;
		float radRot = Rotation * 3.14159265359f / 180;
		int y = (cos(radRot) * (DistFromCenter));
		int x = (sin(radRot) * (DistFromCenter));
		Plot->SetPosition(DirectX::XMFLOAT2(x, y));
		Plot->Rotation = Rotation;
		Plot->DistanceFromCenter = DistFromCenter;
		Rings[2]->PlantPlot(std::move(Plot));
	}

	for (int i = 0; i < 3; i++)
	{
		Rings[i]->BindPlotsColor();
	}
	ITexture* AreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/Tower.png", "AreaTower");
	IRenderable* AreaTowerRemderable = Graphics->CreateFloat4Billboard(ColorChangeShader, AreaTowerTexture, nullptr);
	TowerClones[0] = std::make_unique<AreaTower>(ColorChangeShader, AreaTowerRemderable);
	ITexture* GroundAreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/GroundTower.png", "GroundAreaTower");
	IRenderable* GroundAreaTowerRenderable = Graphics->CreateFloat4Billboard(ColorChangeShader, AreaTowerTexture, nullptr);
	TowerClones[1] = std::make_unique<GroundAreaTower>(ColorChangeShader, GroundAreaTowerRenderable);
	CurrencyShop = std::make_unique<Shop>(100);
	ITexture* EnemyPackTextures = Graphics->CreateTexture(L"Resource/Textures/Fast.png", "EnemyPack");
	ITexture* EnemyFlyTextures = Graphics->CreateTexture(L"Resource/Textures/Flyer.png", "EnemyFly");
	ITexture* EnemySlowTextures = Graphics->CreateTexture(L"Resource/Textures/Slow.png", "EnemySlow");
	
	Wave.Init(Graphics, ColorChangeShader, EnemyPackTextures, EnemyFlyTextures, EnemySlowTextures);
	for (int i = 0; i < 8; i++)
	{
		Wave.AddNewSpawnArea(SpawnAreas[i]);
	}
	return true;
}

bool GameLevel::LoadWaves()
{
	int WaveNumber = 1;
	//Wave 1
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 2, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 5, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 5, 10, WaveNumber);
	WaveNumber++;
	//Wave 3
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 5, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 15, 10, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 3, 5, WaveNumber);
	WaveNumber++;
	//Wave 3
	Wave.AddNewSpawn(EnemyTypes::Flyers, 5, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 10, 10, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 5, 0, WaveNumber);
	WaveNumber++;
	//Wave 4
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 5, 5, WaveNumber);
	WaveNumber++;
	//Wave 5
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 5, WaveNumber);
	WaveNumber++;
	//Wave 6
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 0, WaveNumber);
	WaveNumber++;
	//Wave 7
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 15, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 15, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 5, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 20, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 20, 0, WaveNumber);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 20, 0, WaveNumber);
	WaveNumber++;
	//Wave 8
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 15, 0, WaveNumber, 0);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 15, 0, WaveNumber, 1);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 5, WaveNumber , 2);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber , 3);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber , 4);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 10, 0, WaveNumber, 5);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 10, 5, WaveNumber, 6);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 30, 0, WaveNumber, 7);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 20, 0, WaveNumber, 6);
	Wave.AddNewSpawn(EnemyTypes::FastPacks, 20, 0, WaveNumber, 5);
	Wave.AddNewSpawn(EnemyTypes::Flyers, 30, 0, WaveNumber, 5);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 20, 0, WaveNumber, 0);
	Wave.AddNewSpawn(EnemyTypes::SlowGrunts, 20, 0, WaveNumber, 1);
	WaveNumber++;

	return true;
}

bool GameLevel::LoadUI(float screenX, float screenY)
{
	IShader* ButtonShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	ITexture* ButtonTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");
	IRenderable* StartRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* StartText = Graphics->CreateText("Start Next Wave", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	StartNextWaveButton = std::make_unique<TextButton>(StartRender, StartText, ButtonShader, screenX, screenY);
	StartNextWaveButton->SetPosition(-700, -400);
	StartNextWaveButton->SetButtonScale(4, 2);
	StartNextWaveButton->AddTextPosition(-200, 25);
	StartNextWaveButton->Register(Graphics);
	StartNextWaveButton->Interact.BoundFunction = std::bind(&GameLevel::StartNextWave, this);
	IRenderable* OpenRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* OpenText = Graphics->CreateText("Open Shop", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	OpenShopButton = std::make_unique<TextButton>(OpenRender, OpenText, ButtonShader, screenX, screenY);
	OpenShopButton->SetPosition(0, -400);
	OpenShopButton->SetButtonScale(4, 2);
	OpenShopButton->AddTextPosition(-200, 25);
	OpenShopButton->Register(Graphics);
	OpenShopButton->Interact.BoundFunction = std::bind(&GameLevel::OpenShop, this);
	IRenderable* QuitRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* QuitText = Graphics->CreateText("Quit Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	QuitButton = std::make_unique<TextButton>(QuitRender, QuitText, ButtonShader, screenX, screenY);
	QuitButton->SetPosition(700, -400);
	QuitButton->SetButtonScale(4, 2);
	QuitButton->AddTextPosition(-200, 25);
	QuitButton->Register(Graphics);
	QuitButton->Interact.BoundFunction = std::bind(&GameLevel::QuitGame, this);
	IRenderable* EndRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* EndButtonText = Graphics->CreateText("End Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	EndButton = std::make_unique<TextButton>(EndRender, EndButtonText, ButtonShader, screenX, screenY);
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

	IText* AreaTowerText = Graphics->CreateText("60 Gold Can attack Sea and Air", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	ITexture* AreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/Tower.png", "TBuy");
	IRenderable* AreaTowerRenderable = Graphics->CreateFloat4Billboard(ButtonShader, AreaTowerTexture, nullptr);
	TowerButtons[0] =std::make_unique<TextButton>(AreaTowerRenderable, AreaTowerText, ButtonShader, screenX, screenY);
	TowerButtons[0]->SetPosition(-300, 0);
	TowerButtons[0]->SetButtonScale(2, 2);
	TowerButtons[0]->AddTextPosition(-400, 200);
	TowerButtons[0]->Register(Graphics);
	TowerButtons[0]->Unregister(Graphics);
	TowerButtons[0]->Interact.SetHighlightColor(0.7, 1, 0.7, 1);
	TowerButtons[0]->Interact.BoundFunction = std::bind(&GameLevel::SpawnAreaTower, this);
	IText* GroundAreaTowerText = Graphics->CreateText("40 Gold Can attack Sea", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	ITexture* GroundAreaTowerTexture = Graphics->CreateTexture(L"Resource/Textures/GroundTower.png", "GTBuy");
	IRenderable* GroundAreaTowerRenderable = Graphics->CreateFloat4Billboard(ButtonShader, GroundAreaTowerTexture, nullptr);
	TowerButtons[1] = std::make_unique<TextButton>(GroundAreaTowerRenderable, GroundAreaTowerText, ButtonShader, screenX, screenY);
	TowerButtons[1]->SetPosition(300, 0);
	TowerButtons[1]->SetButtonScale(2, 2);
	TowerButtons[1]->AddTextPosition(-300, -150);
	TowerButtons[1]->Register(Graphics);
	TowerButtons[1]->Unregister(Graphics);
	TowerButtons[1]->Interact.SetHighlightColor(0.7, 1, 0.7, 1);
	TowerButtons[1]->Interact.BoundFunction = std::bind(&GameLevel::SpawnGroundAreaTower, this);
	return true;
}

bool GameLevel::LoadUILinks()
{
	ButtonSelector = std::make_shared<InputSelection>(&StartNextWaveButton->Interact);
	ButtonSelector->AddButtonLink(&StartNextWaveButton->Interact, &OpenShopButton->Interact, ButtonDirection::Right);
	ButtonSelector->AddButtonLink(&OpenShopButton->Interact, &StartNextWaveButton->Interact, ButtonDirection::Left);
	ButtonSelector->AddButtonLink(&OpenShopButton->Interact, &QuitButton->Interact, ButtonDirection::Right);
	ButtonSelector->AddButtonLink(&QuitButton->Interact, &OpenShopButton->Interact, ButtonDirection::Left);

	RingGamepadSelection = std::make_unique<RingSelection>(Rings[0]);
	Rings[0]->Interact.Highlighted();
	RingGamepadSelection->AddLink(Rings[0], Rings[1], true);
	RingGamepadSelection->AddLink(Rings[1], Rings[0], false);
	RingGamepadSelection->AddLink(Rings[1], Rings[2], true);
	RingGamepadSelection->AddLink(Rings[2], Rings[1], false);

	ShopSelector = std::make_shared<InputSelection>(&TowerButtons[0]->Interact);
	ShopSelector->AddButtonLink(&TowerButtons[0]->Interact, &TowerButtons[1]->Interact, ButtonDirection::Right);
	ShopSelector->AddButtonLink(&TowerButtons[1]->Interact, &TowerButtons[0]->Interact, ButtonDirection::Left);
	ShopSelector->PreviousMenuFunction = std::bind(&GameLevel::CloseShop, this);

	EndSelector = std::make_shared<InputSelection>(&EndButton->Interact);
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
			if (Rings[i]->IsPlotAvailable())
			{
				std::unique_ptr<Tower> TowerIn = CurrencyShop->CreateTower(TowerClones[0], Graphics);
				TowerIn->SetScale(2, 2);
				TowerIn->Register(Graphics);
				TowerIn->SetScale(0.8f, 0.8f);
				CurrencyShop->Spend(TowerIn->GetCost());
				Rings[i]->PlantTower(std::move(TowerIn));
				
				Rings[i]->BindPlotsColor();
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
			if (Rings[i]->IsPlotAvailable())
			{
				std::unique_ptr<Tower> TowerIn =CurrencyShop->CreateTower(TowerClones[1], Graphics);
				TowerIn->SetScale(2, 2);
				TowerIn->Register(Graphics);
				TowerIn->SetScale(0.8f, 0.8f);
				CurrencyShop->Spend(TowerIn->GetCost());
				Rings[i]->PlantTower(std::move(TowerIn));
				Rings[i]->BindPlotsColor();
				return;
			}
		}
	}
}

void GameLevel::QuitGame()
{
	LevelSwitchKey = LevelId::MainMenuLevel;
}
