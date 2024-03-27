#include "GroundAreaTower.h"
#include "../Enemies/Enemy.h"
#include "../Shop/Shop.h"
GroundAreaTower::GroundAreaTower(IShader* ShaderIn, IRenderable* RenderableIn) :
	Tower(ShaderIn, RenderableIn, 4.0f, 80,1.5f,40)
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

std::unique_ptr<Tower> GroundAreaTower::Clone(IGraphics* Graphics) const
{
	IRenderable* Renderable = Graphics->CreateFloat4Billboard(Shader, Graphics->GetTexture("GroundAreaTower"), nullptr);
	return std::make_unique<GroundAreaTower>(Shader, Renderable);
}
