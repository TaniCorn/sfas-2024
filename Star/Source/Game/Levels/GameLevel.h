#pragma once
#include "../../Engine/ILevel.h"
#include "../Enemies/WaveManager.h"
#include "../Base/HomeBase.h"
#include "../Base/RingSelection.h"
#include "../Base/DefenceRing.h"
#include "../Shop/Shop.h"
#include <memory>
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
	void OpenShop();
	void CloseShop();
	void SpawnAreaTower();
	void SpawnGroundAreaTower();
	void QuitGame();
	TextButton* StartNextWaveButton;
	TextButton* OpenShopButton;
	TextButton* QuitButton;
	IText* CurrencyIndicator;
	std::string CurrencyString;
	IText* RoundIndicator;
	std::string RoundString;
	IText* HealthIndicator;
	std::string HealthString;
	IText* EndText;
	TextButton* EndButton;

	InputSelection* ButtonSelector;
	InputSelection* ShopSelector;
	InputSelection* EndSelector;
	InputSelection* CurrentSelector;

	std::unique_ptr<Shop> CurrencyShop;
	std::unique_ptr<TextButton> TowerButtons[2];
	std::unique_ptr<Tower> TowerClones[2];
	RingSelection* RingGamepadSelection;
	DefenceRing* Rings[3];
	std::unique_ptr<HomeBase> Base;
	WaveManager Wave;
	DirectX::XMFLOAT2 SpawnAreas[8];

	bool bPaused = false;
};

