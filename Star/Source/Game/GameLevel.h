#pragma once
#include "../../Source/Engine/ILevel.h"

class IRenderable;
class TextButton;
class IText;
class InputSelection;

class GameLevel : public ILevel
{
	public:
	GameLevel(IGraphics* Graphics, IInput* InputIn);
	virtual ~GameLevel();

	virtual bool Load();
	virtual void Update(float DeltaTime);
	virtual void Cleanup();

private:
	InputSelection* GamepadSelection;
	TextButton* Buttons[2];
};

