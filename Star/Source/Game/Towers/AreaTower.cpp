#include "AreaTower.h"
#include "../Enemies/Enemy.h"
AreaTower::AreaTower(IShader* ShaderIn, IRenderable* RenderableIn, DirectX::XMFLOAT2 PositionIn) :
	Tower(ShaderIn, RenderableIn, 2, 300, 1.5f, PositionIn)
{
}

void AreaTower::AttackUpdate(const std::vector<Enemy*>& Enemies)
{
	if (bAttack)
	{
		std::vector<Enemy*> EnemiesToHit;
		for (int i = 0; i < Enemies.size(); i++)
		{
			if (IsEnemyInRange(Enemies[i]))
			{
				EnemiesToHit.push_back(Enemies[i]);
			}
		}

		bAttack = false;
		if (EnemiesToHit.size() == 0)
		{
			return;
		}

		for (int i = 0; i < EnemiesToHit.size(); i++)
		{
			EnemiesToHit[i]->DamageEntity(Damage);
		}
	}
}
