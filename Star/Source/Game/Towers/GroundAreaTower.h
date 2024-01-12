#pragma once
#include "Tower.h"
class GroundAreaTower : public Tower
{
public:
	GroundAreaTower(IShader* ShaderIn, IRenderable* RenderableIn, DirectX::XMFLOAT2 PositionIn);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies);
};

