#pragma once
#include "../Components/EntityHealth.h"
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../Components/ColorHighlighting.h"
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
	void Init(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	virtual void DamageEntity(float Amount);
	bool IsAlive();
	void Spawn(DirectX::XMFLOAT2 Location);
	virtual void Update(float DeltaTime);
	void SetPosition(DirectX::XMFLOAT2 Location);

	EntityHealth Health;
	static EntityHealth* Target;
	static DirectX::XMFLOAT2 TargetPosition;
	ColorHighlighting ColorHighlight;
protected:
	void MoveTowardsTarget(float DeltaTime);
	void SetStats(float HealthIn, float DamageIn, float SpeedIn, float AttackCooldownIn, bool bCanFly);
	IShader* Shader;
	IRenderable* CurrentTexture;

	float Damage;
	float Speed;
	bool bFlying;
	bool bAlive;
	DirectX::XMFLOAT2 Position;

};

