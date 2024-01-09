#pragma once

class IGraphics;
class IInput;

enum Level
{
	SplashScreenLevel,
	MainMenuLevel,
	SettingsMenuLevel

};
class ILevel
{
public:
	ILevel(IGraphics* GraphicsIn, IInput* InputIn);
	virtual ~ILevel();

	virtual Level LevelSwitch() = 0;
	virtual bool Load() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Cleanup() = 0;

protected:
	Level LevelSwitchKey;
	IGraphics* Graphics;
	IInput* Input;
};

