#pragma once

#include "../IDamageable.h"
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include <DirectXMath.h>

class IShader;

enum EnemyTypes {
	FastPack,
	SlowGrunts,
	Flyers
};
class IEnemy : public IRegisteredObject, public IDamageable
{
public:
	IEnemy();
	IEnemy(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy);
	void Init(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	virtual float GetHealth();
	virtual void DamageEntity(float Amount);
	virtual DirectX::XMFLOAT2 GetPosition();
	virtual void SetPosition(DirectX::XMFLOAT2 PositionIn);

	virtual void Update(float DeltaTime);

	void MoveTowardsTarget(float DeltaTime);
protected:

	void SetStats(float HealthIn, float DamageIn, float SpeedIn, float AttackCooldownIn, bool bCanFly);
	IDamageable* Target;
	IShader* Shader;
	IRenderable* CurrentTexture;
	float Health;
	float Damage;
	float Speed;
	float AttackCooldown;
	float AttackTimer;
	bool bFlying;
	
	DirectX::XMFLOAT2 Position;
};

