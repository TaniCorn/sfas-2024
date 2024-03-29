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
	int GetCurrentGold() const;
	bool CanPurchase(const int GoldSpend) const;
	void AddGold(const int Amount);
	void Spend(const int GoldSpend);

	std::unique_ptr<Tower> CreateTower(std::unique_ptr<Tower> const &Clone, IGraphics* Graphics) const;
private:
	int Gold;
};

