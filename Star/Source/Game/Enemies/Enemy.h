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
	bool IsAlive() const;
	bool Flying() const;
	void Spawn(DirectX::XMFLOAT2 Location);
	virtual void Update(float DeltaTime);
	void SetPosition(DirectX::XMFLOAT2 Location);
	void SetRotation(float Rotation);
	DirectX::XMFLOAT2 GetPosition() const;
	int GetGoldGain();

	EntityHealth Health;
	static EntityHealth* Target;
	static DirectX::XMFLOAT2 TargetPosition;
	ColorHighlighting ColorHighlight;
protected:
	void MoveTowardsTarget(float DeltaTime);
	void SetStats(float HealthIn, float DamageIn, float SpeedIn, int Gold, bool bCanFly);
	IShader* Shader;
	IRenderable* CurrentTexture;

	float Damage;
	float Speed;
	bool bFlying;
	bool bAlive;
	int GoldGain;
	DirectX::XMFLOAT2 Position;

};

