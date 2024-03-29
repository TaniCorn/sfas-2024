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

	virtual bool Load() override;
	virtual void Update(float DeltaTime) override;
	virtual void Cleanup() override;

private:
	void QuitGame();
	void StartGame();

	std::unique_ptr<InputSelection> GamepadSelection;
	std::unique_ptr <TextButton> Buttons[2];

};

