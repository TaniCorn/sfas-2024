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
	Tower(IShader* ShaderIn, IRenderable* RenderableIn, float DamageIn, float RangeIn, float AttackCooldownIn, int Cost);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);

	virtual void Update(float DeltaTime);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies) = 0;
	void SetPosition(DirectX::XMFLOAT2 Location);
	int GetCost();
	void SetScale(float x, float y);
	bool IsEnemyInRange(const Enemy* CurrentEnemy) const;
	ColorHighlighting ColorHighlight;
	IRenderable* GetRenderable();
	virtual std::unique_ptr<Tower> Clone(IGraphics* Graphics) = 0;
protected:
	IShader* Shader;
	IRenderable* CurrentTexture;
	float Range;
	float Damage;

	float AttackCooldown;
	float AttackTimer = 0;
	bool bAttack = false;
	int Cost;
};

