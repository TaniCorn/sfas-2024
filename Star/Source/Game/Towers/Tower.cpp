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
	CurrentTexture->SetPosition(Position->x, Position->y);

}

int Tower::GetCost()
{
	return Cost;
}

void Tower::LinkPosition(DirectX::XMFLOAT2& Location)
{
	Position = &Location;
	CurrentTexture->SetPosition(Position->x, Position->y);
}

void Tower::SetScale(float x, float y)
{
	CurrentTexture->SetScale(x, y);
}

bool Tower::IsEnemyInRange(const Enemy* CurrentEnemy) const
{
	DirectX::XMFLOAT2 Vector = DXHelper::Subtract(CurrentEnemy->GetPosition(), *Position);
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
