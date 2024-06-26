#pragma once
#include "../Components/EntityHealth.h"
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../Components/ColorHighlighting.h"
#include <DirectXMath.h>

class IShader;

enum class EnemyTypes {
	FastPacks,
	SlowGrunts,
	Flyers
};

class Enemy : public IRegisteredObject
{
public:
	static EntityHealth* TargetHealthObject;
	static DirectX::XMFLOAT2 TargetPosition;
	Enemy();
	Enemy(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy);
	virtual void Register(IGraphics* GraphicsIn) override;
	virtual void Unregister(IGraphics* GraphicsIn) override;
	

	bool IsAlive() const;
	bool Flying() const;
	DirectX::XMFLOAT2 GetPosition() const;
	int GetGoldGain() const;

	void DamageEntity(float Amount);
	void Update(float DeltaTime);
	void Spawn(const DirectX::XMFLOAT2 Location);
	void SetPosition(DirectX::XMFLOAT2 Location);
	void SetRotation(float Rotation);

	
	EntityHealth Health;
	ColorHighlighting ColorHighlight;
protected:
	void MoveTowardsTarget(float DeltaTime);
	void MoveAndRotate(float DeltaTime, DirectX::XMFLOAT2 Direction);
	void SetStats(const float HealthIn, const float DamageIn, const float SpeedIn, const int Gold, const bool bCanFly);
	

	IShader* Shader;
	IRenderable* CurrentTexture;
	bool bFlying;
	float Damage;
	float Speed;
	bool bAlive;
	int GoldGain;
	DirectX::XMFLOAT2 Position;

};

