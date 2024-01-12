#pragma once

class IGraphics;
class IInput;

enum Level
{
	QuitProgram,
	SplashScreenLevel,
	MainMenuLevel,
	SettingsMenuLevel,
	GameLevel1

};
class ILevel
{
public:
	ILevel(IGraphics* GraphicsIn, IInput* InputIn);
	virtual ~ILevel();

	virtual Level LevelSwitch();
	virtual bool Load() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Cleanup() = 0;

protected:
	Level LevelSwitchKey;
	IGraphics* Graphics;
	IInput* Input;
};

