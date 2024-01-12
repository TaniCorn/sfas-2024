#pragma once
#include "Tower.h"
class AreaTower : public Tower
{
	AreaTower(IShader* ShaderIn, IRenderable* RenderableIn, DirectX::XMFLOAT2 PositionIn);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies);
};

