#pragma once
#include "../../Source/Engine/ILevel.h"
#include "Enemies/Enemy.h"
#include "Towers/HomeBase.h"

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
	bool LoadEntities();
	bool LoadUI(float screenX, float screenY);
	void QuitGame();
	TextButton* TestButton;
	InputSelection* GamepadSelection;


	HomeBase* Base;
	Enemy EnemyPool[60];
};

