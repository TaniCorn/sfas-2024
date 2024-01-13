#include "AreaTower.h"
#include "../Enemies/Enemy.h"
AreaTower::AreaTower(IShader* ShaderIn, IRenderable* RenderableIn) :
	Tower(ShaderIn, RenderableIn, 5, 1400, 1.5f,60)
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
Tower* AreaTower::Clone(IGraphics* Graphics)
{
	IRenderable* Renderable = Graphics->CreateFloat4Billboard(Shader, Graphics->GetTexture("AreaTower"), nullptr);
	return new AreaTower(Shader, Renderable);
}
