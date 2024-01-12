#include "Tower.h"
#include "../Enemies/Enemy.h"
#include "../../Engine/Implementation/DXMathHelper.h"
Tower::Tower(IShader* ShaderIn, IRenderable* RenderableIn, float DamageIn, float RangeIn, float AttackCooldownIn, DirectX::XMFLOAT2 PositionIn)  :
	Shader(ShaderIn), CurrentTexture(RenderableIn), Damage(DamageIn), Range(RangeIn), AttackCooldown(AttackCooldownIn), Position(PositionIn)
{

}
void Tower::Register(IGraphics* GraphicsIn)
{
	GraphicsIn->AddSpriteToRender(Shader, CurrentTexture);
}
void Tower::Unregister(IGraphics* GraphicsIn)
{
	GraphicsIn->RemoveSpriteFromRender(Shader, CurrentTexture);
}

void Tower::Update(float DeltaTime)
{
	if (AttackTimer < 0)
	{
		bAttack = true;
		AttackTimer = AttackCooldown;
	}
	AttackTimer -= DeltaTime;
}

void Tower::SetPosition(DirectX::XMFLOAT2 Location)
{
	Position = Location;
	CurrentTexture->SetPosition(Location.x, Location.y);
}

bool Tower::IsEnemyInRange(const Enemy* CurrentEnemy) const
{
	DirectX::XMFLOAT2 Vector = DXHelper::Subtract(CurrentEnemy->GetPosition(), Position);
	float Distance = DXHelper::Magnitude(Vector);
	if (Distance > Range)
	{
		return false;
	}
	else
	{
		return true;
	}

}
