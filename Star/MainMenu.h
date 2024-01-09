#pragma once
#include "ILevel.h"

class IRenderable;

class MainMenu : public ILevel
{
public:
	MainMenu(IGraphics* Graphics, IInput* InputIn);
	virtual ~MainMenu();

	virtual Level LevelSwitch();
	virtual bool Load();
	virtual void Update(float DeltaTime);
	virtual void Cleanup();

private:


};

