#pragma once

class IGraphics;
class IInput;

//TODO: Remove level enum class to a scalable system
enum class LevelId
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

	virtual LevelId LevelSwitch();
	virtual bool Load() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Cleanup() = 0;

protected:
	LevelId LevelSwitchKey;
	IGraphics* Graphics;
	IInput* Input;
};

