#include "Tower.h"
#include "../Enemies/Enemy.h"
#include "../../Engine/Implementation/DXMathHelper.h"
#include "../Base/TowerPlot.h"
Tower::Tower(IShader* ShaderIn, IRenderable* RenderableIn, float DamageIn, float RangeIn, float AttackCooldownIn,int CostIn)  :
	Shader(ShaderIn), CurrentTexture(RenderableIn), Damage(DamageIn), Range(RangeIn), AttackCooldown(AttackCooldownIn), Cost(CostIn)
{
	RenderableIn->BindParam(ColorHighlight.GetColorBind());
}
void Tower::Register(IGraphics* GraphicsIn)
{
	GraphicsIn->AddSpriteToRender(Shader, CurrentTexture, 2);
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
	CurrentTexture->SetPosition(Location.x, Location.y);
}

int Tower::GetCost()
{
	return Cost;
}

void Tower::SetScale(float x, float y)
{
	CurrentTexture->SetScale(x, y);
}

bool Tower::IsEnemyInRange(const Enemy* CurrentEnemy) const
{
	DirectX::XMFLOAT2 Vector = DXHelper::Subtract(CurrentEnemy->GetPosition(), 
		DirectX::XMFLOAT2(CurrentTexture->GetTransform().PositionX, CurrentTexture->GetTransform().PositionY));
	float Distance = DXHelper::MagnitudeSqrRoot(Vector);
	if (Distance > Range)
	{
		return false;
	}
	else
	{
		return true;
	}

}

IRenderable* Tower::GetRenderable()
{
	return CurrentTexture;
}
