#pragma once
class IGraphics;
class IShader;
class ITexture;
class TextButton;
class Tower;

#include <vector>
#include <set>
#include <memory>

class Shop
{
public:
	Shop(int StartingGold);
	int GetCurrentGold();
	void AddGold(int Amount);
	void AddButton(TextButton* Button, Tower* PurchaseTower);
	void Spend(int GoldSpend);
	bool CanPurchase(int GoldSpend);

	Tower* CreateTower(std::unique_ptr<Tower> const &Clone, IGraphics* Graphics);
	std::set<Tower*> TowersCreated;
private:
	int Gold;
	std::vector<std::pair<TextButton*,Tower*>> PurchaseButtons;
};

