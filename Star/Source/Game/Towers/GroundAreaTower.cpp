#include "GroundAreaTower.h"
#include "../Enemies/Enemy.h"
GroundAreaTower::GroundAreaTower(IShader* ShaderIn, IRenderable* RenderableIn, DirectX::XMFLOAT2 PositionIn) :
	Tower(ShaderIn, RenderableIn, 3.0f, 300.0f,0.5f, PositionIn)
{
}

void GroundAreaTower::AttackUpdate(const std::vector<Enemy*>& Enemies)
{
	if (bAttack)
	{
		std::vector<Enemy*> EnemiesToHit;
		for (int i = 0; i < Enemies.size(); i++)
		{
			if (IsEnemyInRange(Enemies[i]))
			{
				if (!Enemies[i]->Flying())
				{
					EnemiesToHit.push_back(Enemies[i]);
				}
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
