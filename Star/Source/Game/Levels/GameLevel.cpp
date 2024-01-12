#include "GameLevel.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "../../Engine/Implementation/InputSelection.h"
#include "../UI/TextButton.h"
#include "../../Engine/IText.h"

GameLevel::GameLevel(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = GameLevel1;
}

GameLevel::~GameLevel()
{
	delete GamepadSelection;
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

	Enemy::TargetPosition = Base->Position;
	Enemy::Target = &Base->Health;
    return true;
}

void GameLevel::Update(float DeltaTime)
{
	GamepadSelection->Update(Input);
	Base->Update(DeltaTime);
	Wave.Update(DeltaTime);
	if (Wave.CanStartNextWave())
	{
		StartButton->Register(Graphics);
	}
	else 
	{
		StartButton->Unregister(Graphics);
	}

	if (Base->Health.Health < 0)
	{
		//Lose Game
		//Popup quit/retry UI
	}

	if (Wave.HasWon())
	{
		//End Game
		//Popup win UI
	}

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
	BaseRender->BindParam(Base->ColorHighlight.GetColorBind());

	ITexture* EnemyPackTextures = Graphics->CreateTexture(L"Resource/Textures/Fast.png", "EnemyPack");
	ITexture* EnemyFlyTextures = Graphics->CreateTexture(L"Resource/Textures/Fly.png", "EnemyFly");
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
	StartButton = new TextButton(StartRender, StartText, ButtonShader, screenX, screenY);
	StartButton->SetPosition(0, -300);
	StartButton->SetButtonScale(4, 2);
	StartButton->AddTextPosition(-200, 25);
	StartButton->Register(Graphics);
	StartRender->BindParam(StartButton->Interact.GetColorBind());
	//StartButton->Unregister(Graphics);
	StartButton->Interact.BoundFunction = std::bind(&GameLevel::StartNextWave, this);


	GamepadSelection = new InputSelection(&StartButton->Interact);
	return true;
}

void GameLevel::QuitGame()
{
	LevelSwitchKey = MainMenuLevel;
}
