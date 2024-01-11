#pragma once
#include "../../Source/Engine/ILevel.h"

class IRenderable;
class TextButton;
class IText;
#include <string>
class MainMenu : public ILevel
{
public:
	MainMenu(IGraphics* Graphics, IInput* InputIn);
	virtual ~MainMenu();

	virtual bool Load();
	virtual void Update(float DeltaTime);
	virtual void Cleanup();

private:
	TextButton* StartButton;
	TextButton* QuitButton;
	IText* DebugText;

	float Color[4] = { 1,0,1,0 };
	float HighlightColor[4] = { 1,1,1,1 };
	std::string DebugString;
	int ButtonSelection = 0;
	const int HighestButtonSelection = 1;
};

