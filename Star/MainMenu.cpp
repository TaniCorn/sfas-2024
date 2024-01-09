#include "MainMenu.h"

MainMenu::MainMenu(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
}

MainMenu::~MainMenu()
{
}

Level MainMenu::LevelSwitch()
{
	return Level();
}

bool MainMenu::Load()
{
	return false;
}

void MainMenu::Update(float DeltaTime)
{
}

void MainMenu::Cleanup()
{
}
