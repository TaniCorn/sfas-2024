#pragma once
namespace DirectX {
	struct XMFLOAT2;
}
class IDamageable
{
public:
	virtual float GetHealth() = 0;
	virtual void DamageEntity(float Amount) = 0;
	virtual DirectX::XMFLOAT2 GetPosition() = 0;
	virtual void SetPosition(DirectX::XMFLOAT2 PositionIn) = 0;
};

