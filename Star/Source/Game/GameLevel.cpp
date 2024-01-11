#include "GameLevel.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "../Engine/Implementation/InputSelection.h"

GameLevel::GameLevel(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = MainMenuLevel;
}

GameLevel::~GameLevel()
{
	delete GamepadSelection;
	delete Buttons[0];
	delete Buttons[1];
}

bool GameLevel::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY = Graphics->GetWindowHeight();


    return true;
}

void GameLevel::Update(float DeltaTime)
{
	GamepadSelection->Update(Input);
}

void GameLevel::Cleanup()
{
	Graphics->Cleanup();
}
