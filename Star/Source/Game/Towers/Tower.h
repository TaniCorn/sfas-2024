#pragma once
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../Components/ColorHighlighting.h"
#include <vector>
#include <DirectXMath.h>

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

	int GetCost();
	void LinkPosition(DirectX::XMFLOAT2& Location);
	void SetScale(float x, float y);
	bool IsEnemyInRange(const Enemy* CurrentEnemy) const;
	ColorHighlighting ColorHighlight;
	IRenderable* GetRenderable();
	virtual Tower* Clone(IGraphics* Graphics) = 0;
protected:
	IShader* Shader;
	IRenderable* CurrentTexture;
	DirectX::XMFLOAT2* Position;
	float Range;
	float Damage;

	float AttackCooldown;
	float AttackTimer = 0;
	bool bAttack = false;
	int Cost;
};

