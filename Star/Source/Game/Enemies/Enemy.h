#pragma once

#include "../EntityHealth.h"
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../../../ColorHighlighting.h"
#include <DirectXMath.h>

class IShader;

enum EnemyTypes {
	FastPack,
	SlowGrunts,
	Flyers
};
class Enemy : public IRegisteredObject
{
public:
	Enemy();
	Enemy(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy);
	void Init(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	virtual void DamageEntity(float Amount);

	virtual void Update(float DeltaTime);

	EntityHealth Health;
	DirectX::XMFLOAT2 Position;
	EntityHealth* Target;
	DirectX::XMFLOAT2 TargetPosition;
	ColorHighlighting ColorHighlight;
protected:
	void MoveTowardsTarget(float DeltaTime);
	void SetStats(float HealthIn, float DamageIn, float SpeedIn, float AttackCooldownIn, bool bCanFly);
	IShader* Shader;
	IRenderable* CurrentTexture;

	float Damage;
	float Speed;
	float AttackCooldown;
	float AttackTimer;
	bool bFlying;
	bool bAlive;
};

