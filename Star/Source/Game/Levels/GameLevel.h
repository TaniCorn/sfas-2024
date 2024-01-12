#pragma once
#include "../../Engine/ILevel.h"
#include "../Enemies/WaveManager.h"
#include "../Base/HomeBase.h"
#include "../../../RingSelection.h"
#include "../Base/DefenceRing.h"


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
	bool LoadUILinks();
	void QuitGame();
	TextButton* StartNextWaveButton;
	InputSelection* GamepadSelection;

	TowerPlot* Plots[3];
	RingSelection* RingGamepadSelection;
	DefenceRing* Rings[3];
	HomeBase* Base;
	WaveManager Wave;
	DirectX::XMFLOAT2 SpawnAreas[8];
};

