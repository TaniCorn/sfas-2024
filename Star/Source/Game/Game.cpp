#include "Game.h"

#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "../Game/Levels/SplashScreen.h"
#include "../Game/Levels/MainMenu.h"
#include "../Game/Levels/GameLevel.h"
#include <ctime>
#include <math.h>

#define CLAMP(v, x, y) fmin(fmax(v, x), y)

constexpr float Pie = 3.14159265359f;
constexpr float TwoPies = Pie * 2.0f;
constexpr float DeltaTime = 0.016f;
constexpr float SpinSpeed = 0.1f;
constexpr float WinTolerance = Pie / 10.0f;

IApplication* GetApplication(IGraphics* Graphics, IInput* Input)
{
	return new Game(Graphics, Input);
}

Game::Game(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn), Rings(), Arrow(nullptr), SelectedRing(), State()
{
}

Game::~Game()
{
}

bool Game::IsValid()
{
	return !bQuitGame;
}

bool Game::Load()
{
	CurrentLevel = new SplashScreen(Graphics, Input);
	CurrentLevel->Load();
	CurrentLevelIdentifier = SplashScreenLevel;
	return true;
}

void Game::Update(float DeltaTime)
{
	CurrentLevel->Update(DeltaTime);

	if (CurrentLevelIdentifier != CurrentLevel->LevelSwitch())
	{
		SwitchLevel(CurrentLevel->LevelSwitch());
	}
}

void Game::Cleanup()
{

}

void Game::SwitchLevel(Level NextLevelIdentfier)
{
	CurrentLevel->Cleanup();
	delete CurrentLevel;

	switch (NextLevelIdentfier)
	{
	case QuitProgram:
		bQuitGame = true;
		return;
	case MainMenuLevel:
		CurrentLevel = new MainMenu(Graphics, Input);
		break;
	case SettingsMenuLevel:
		//CurrentLevel = new
		break;
	case GameLevel1:
		CurrentLevel = new GameLevel(Graphics, Input);
		break;
	default:
		CurrentLevel = new SplashScreen(Graphics, Input);
		break;
	}

	CurrentLevelIdentifier = NextLevelIdentfier;
	if (!CurrentLevel->Load())
	{
		CurrentLevel->Cleanup();
		delete CurrentLevel;
		CurrentLevel = new SplashScreen(Graphics, Input);
		CurrentLevel->Load();
		CurrentLevelIdentifier = SplashScreenLevel;
	}
}
