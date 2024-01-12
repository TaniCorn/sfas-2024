#pragma once
#include "Tower.h"
class AreaTower : public Tower
{
public:
	AreaTower(IShader* ShaderIn, IRenderable* RenderableIn);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies);
	virtual Tower* Clone(IGraphics* Graphics);
};

