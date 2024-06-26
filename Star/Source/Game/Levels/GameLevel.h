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

	virtual bool Load() override;
	virtual void Update(float DeltaTime) override;
	virtual void Cleanup() override;

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
	//UI
	std::unique_ptr<TextButton> StartNextWaveButton;
	std::unique_ptr<TextButton> OpenShopButton;
	std::unique_ptr<TextButton> QuitButton;
	IText* CurrencyIndicator;
	std::string CurrencyString = "Null";
	IText* RoundIndicator;
	std::string RoundString = "Null";
	IText* HealthIndicator;
	std::string HealthString = "Null";
	IText* EndText;
	std::unique_ptr<TextButton> EndButton;

	//Input Selections
	std::shared_ptr<InputSelection> ButtonSelector;
	std::shared_ptr<InputSelection> ShopSelector;
	std::shared_ptr<InputSelection> EndSelector;
	std::shared_ptr<InputSelection> CurrentSelector;

	//Gameobjects
	std::unique_ptr<Shop> CurrencyShop;
	std::unique_ptr<TextButton> TowerButtons[2];
	std::unique_ptr<Tower> TowerClones[2];
	WaveManager Wave;
	DirectX::XMFLOAT2 SpawnAreas[8];

	std::unique_ptr<RingSelection> RingGamepadSelection;
	std::shared_ptr<DefenceRing> Rings[3];
	std::unique_ptr<HomeBase> Base;


	bool bPaused = false;
};

