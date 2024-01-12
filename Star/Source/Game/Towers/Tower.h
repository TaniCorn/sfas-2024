#pragma once
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../Components/ColorHighlighting.h"
#include <vector>
#include <DirectXMath.h>

class Enemy;

class Tower : public IRegisteredObject
{
public:
	Tower(IShader* ShaderIn, IRenderable* RenderableIn, float DamageIn, float RangeIn, float AttackCooldownIn, DirectX::XMFLOAT2 PositionIn);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);

	virtual void Update(float DeltaTime);
	virtual void AttackUpdate(const std::vector<Enemy*>& Enemies) = 0;

	void SetPosition(DirectX::XMFLOAT2 Location);
	bool IsEnemyInRange(const Enemy* CurrentEnemy) const;
	ColorHighlighting ColorHighlight;
protected:
	IShader* Shader;
	IRenderable* CurrentTexture;

	float Range;
	float Damage;
	DirectX::XMFLOAT2 Position;

	float AttackCooldown;
	float AttackTimer = 0;
	bool bAttack = false;
};

