#include "AreaTower.h"
#include "../Enemies/Enemy.h"
AreaTower::AreaTower(IShader* ShaderIn, IRenderable* RenderableIn) :
	Tower(ShaderIn, RenderableIn, 1, 120*120, 0.5f,60)
{
}

void AreaTower::AttackUpdate(const std::vector<Enemy*>& Enemies)
{
	if (bAttack)
	{
		//Push enemies to damange into temporary vector
		std::vector<Enemy*> EnemiesToHit;
		for (int i = 0; i < Enemies.size(); i++)
		{
			//If any enemy is in range
			if (IsEnemyInRange(Enemies[i]))
			{
				EnemiesToHit.push_back(Enemies[i]);
			}
		}

		//Attack any valid enemies, set bAttack to false regardless if any enemies are hit
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
std::unique_ptr<Tower> AreaTower::Clone(IGraphics* Graphics) const
{
	IRenderable* Renderable = Graphics->CreateFloat4Billboard(Shader, Graphics->GetTexture("AreaTower"), nullptr);
	return std::make_unique<AreaTower>(Shader, Renderable);
}
