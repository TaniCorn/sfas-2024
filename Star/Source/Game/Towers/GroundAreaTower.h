#pragma once
#include "Tower.h"
class GroundAreaTower : public Tower
{
public:
	GroundAreaTower(IShader* ShaderIn, IRenderable* RenderableIn);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies);
	virtual std::unique_ptr<Tower> Clone(IGraphics* Graphics) const;
};

