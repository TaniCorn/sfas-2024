#pragma once
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../Components/ColorHighlighting.h"
#include <vector>
#include <DirectXMath.h>
#include <memory>
class TowerPlot;
class Enemy;

class Tower : public IRegisteredObject
{
public:
	Tower(IShader* ShaderIn, IRenderable* RenderableIn, const float DamageIn, const float RangeIn, const float AttackCooldownIn, const int Cost);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	virtual void Update(float DeltaTime);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies) = 0;
	virtual std::unique_ptr<Tower> Clone(IGraphics* Graphics) const = 0;

	bool IsEnemyInRange(const Enemy* CurrentEnemy) const;
	int GetCost() const;
	IRenderable* GetRenderable() const;
	void SetPosition(const DirectX::XMFLOAT2 Location);
	void SetScale(const float x, const float y);

	ColorHighlighting ColorHighlight;
protected:
	IShader* Shader;
	IRenderable* CurrentTexture;
	const float Range;
	const float Damage;
	const int Cost;
	const float AttackCooldown;

	float AttackTimer = 0;
	bool bAttack = false;
};

