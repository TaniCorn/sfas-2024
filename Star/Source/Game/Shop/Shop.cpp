#include "Shop.h"
#include "../Towers/Tower.h"
Shop::Shop(int StartingGold) : Gold(StartingGold)
{
}

const int Shop::GetCurrentGold() const
{
    return Gold;
}

void Shop::AddGold(const int Amount)
{
    Gold += Amount;
}

void Shop::Spend(const int GoldSpend)
{
    Gold -= GoldSpend;
}

const bool Shop::CanPurchase(const int GoldSpend) const 
{
    if (GoldSpend <= Gold)
    {
        return true;
    }
    return false;
}

std::unique_ptr<Tower> Shop::CreateTower(std::unique_ptr<Tower> const &Clone, IGraphics* Graphics) const
{
    return Clone->Clone(Graphics);
}
