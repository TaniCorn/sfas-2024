#pragma once
#include "../../Engine/ILevel.h"
#include "../Enemies/WaveManager.h"
#include "../Base/HomeBase.h"

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
	void StartNextWave();
	bool LoadArea();
	bool LoadEntities();
	bool LoadWaves();
	bool LoadUI(float screenX, float screenY);
	void QuitGame();
	TextButton* StartButton;
	InputSelection* GamepadSelection;


	HomeBase* Base;
	WaveManager Wave;
	DirectX::XMFLOAT2 SpawnAreas[8];
};

