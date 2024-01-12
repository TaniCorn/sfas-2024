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
	bSuccess = LoadUILinks();
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
	RingGamepadSelection->Update(DeltaTime, Input);
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
	InnerRing->BindParam(Rings[0]->Interact.GetColorBind());
	MiddleRing->BindParam(Rings[1]->Interact.GetColorBind());
	OuterRing->BindParam(Rings[2]->Interact.GetColorBind());

	for (int i = 0; i < 3; i++)
	{
		IRenderable* Plot = Graphics->CreateFloat4Billboard(ColorChangeShader, BaseTexture, nullptr);
		Plots[i] = new TowerPlot(ColorChangeShader, Plot);
		Plot->BindParam(Plots[i]->Interact.GetColorBind());

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


	return true;
}

bool GameLevel::LoadUILinks()
{
	GamepadSelection = new InputSelection(&StartButton->Interact);

	RingGamepadSelection = new RingSelection(Rings[0]);
	RingGamepadSelection->AddLink(Rings[0], Rings[1], true);
	RingGamepadSelection->AddLink(Rings[1], Rings[0], false);
	RingGamepadSelection->AddLink(Rings[1], Rings[2], true);
	RingGamepadSelection->AddLink(Rings[2], Rings[1], false);
	return true;
}

void GameLevel::QuitGame()
{
	LevelSwitchKey = MainMenuLevel;
}
