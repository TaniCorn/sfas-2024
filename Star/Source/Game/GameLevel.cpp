#include "GameLevel.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "../Engine/Implementation/InputSelection.h"
#include "../Game/GameObjects/TextButton.h"
#include "../../Source/Engine/IText.h"

GameLevel::GameLevel(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = GameLevel1;
}

GameLevel::~GameLevel()
{
	delete GamepadSelection;
	delete TestButton;
}

bool GameLevel::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY = Graphics->GetWindowHeight();
	bool bSuccess = true;
	bSuccess = LoadEntities();
	if (!bSuccess)
	{
		return bSuccess;
	}
	bSuccess = LoadUI(screenX, screenY);
	if (!bSuccess)
	{
		return bSuccess;
	}

    return true;
}

void GameLevel::Update(float DeltaTime)
{
	GamepadSelection->Update(Input);
	Base->Update(DeltaTime);
	for (int i = 0; i < 60; i++)
	{
		EnemyPool[i].Update(DeltaTime);
	}
}

void GameLevel::Cleanup()
{
	Graphics->Cleanup();
}

bool GameLevel::LoadEntities()
{
	IShader* ColorChangeShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");

	ITexture* BaseTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");
	IRenderable* BaseRender = Graphics->CreateFloat4Billboard(ColorChangeShader, BaseTexture, nullptr);
	Base = new HomeBase(BaseRender, ColorChangeShader);
	Base->Register(Graphics);
	BaseRender->BindParam(Base->ColorHighlight.GetColorBind());

	ITexture* EnemyPackTextures = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "EnemyPack");
	for (int i = 0; i < 30; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(ColorChangeShader, EnemyPackTextures, nullptr);
		EnemyPool[i].Init(EnemyRender, ColorChangeShader, FastPack);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool->ColorHighlight.GetColorBind());
	}
	ITexture* EnemyFlyTextures = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "EnemyFly");
	for (int i = 30; i < 50; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(ColorChangeShader, EnemyFlyTextures, nullptr);
		EnemyPool[i].Init(EnemyRender, ColorChangeShader, FastPack);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool->ColorHighlight.GetColorBind());
	}
	ITexture* EnemySlowTextures = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "EnemySlow");
	for (int i = 50; i < 60; i++)
	{
		IRenderable* EnemyRender = Graphics->CreateFloat4Billboard(ColorChangeShader, EnemySlowTextures, nullptr);
		EnemyPool[i].Init(EnemyRender, ColorChangeShader, FastPack);
		EnemyPool[i].Register(Graphics);
		EnemyRender->BindParam(EnemyPool->ColorHighlight.GetColorBind());
	}
	return true;
}

bool GameLevel::LoadUI(float screenX, float screenY)
{
	IShader* ButtonShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	ITexture* ButtonTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");
	IRenderable* StartRender = Graphics->CreateFloat4Billboard(ButtonShader, ButtonTexture, nullptr);
	IText* StartText = Graphics->CreateText("Start Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	TestButton = new TextButton(StartRender, StartText, ButtonShader, screenX, screenY);
	TestButton->Register(Graphics);
	TestButton->Interact.BoundFunction = std::bind(&GameLevel::QuitGame, this);


	GamepadSelection = new InputSelection(&TestButton->Interact);
	return true;
}

void GameLevel::QuitGame()
{
	LevelSwitchKey = MainMenuLevel;
}
