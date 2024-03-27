#include "Shop.h"
#include "../Towers/Tower.h"
Shop::Shop(int StartingGold) : Gold(StartingGold)
{
}

int Shop::GetCurrentGold()
{
    return Gold;
}

void Shop::AddGold(int Amount)
{
    Gold += Amount;
}

void Shop::AddButton(TextButton* Button, Tower* PurchaseTower)
{
    PurchaseButtons.push_back(std::pair<TextButton*, Tower*>(Button, PurchaseTower));
}

void Shop::Spend(int GoldSpend)
{
    Gold -= GoldSpend;
}

bool Shop::CanPurchase(int GoldSpend)
{
    if (GoldSpend <= Gold)
    {
        return true;
    }
    return false;
}

Tower* Shop::CreateTower(std::unique_ptr<Tower> const &Clone, IGraphics* Graphics)
{
    Tower* CreatedTower = Clone->Clone(Graphics);
    CreatedTower->SetScale(2, 2);
    CreatedTower->Register(Graphics);
    TowersCreated.insert(CreatedTower);
    return CreatedTower;
}
