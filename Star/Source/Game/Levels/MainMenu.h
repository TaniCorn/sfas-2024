#pragma once
#include "../../Engine/ILevel.h"
#include <memory>
class IRenderable;
class TextButton;
class IText;
class InputSelection;

class MainMenu : public ILevel
{
public:
	MainMenu(IGraphics* Graphics, IInput* InputIn);
	virtual ~MainMenu();

	virtual bool Load();
	virtual void Update(float DeltaTime);
	virtual void Cleanup();

private:
	std::unique_ptr<InputSelection> GamepadSelection;
	std::unique_ptr <TextButton> Buttons[2];
	void QuitGame();
	void StartGame();
};

