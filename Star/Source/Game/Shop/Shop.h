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
	Shop(const int StartingGold);
	const int GetCurrentGold() const;
	void AddGold(const int Amount);
	void AddButton(TextButton* Button, Tower* PurchaseTower);
	void Spend(const int GoldSpend);
	bool CanPurchase(const int GoldSpend) const;

	std::unique_ptr<Tower> CreateTower(std::unique_ptr<Tower> const &Clone, IGraphics* Graphics);
private:
	int Gold;
	std::vector<std::pair<TextButton*,Tower*>> PurchaseButtons;
};

