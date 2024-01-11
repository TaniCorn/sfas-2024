#include "IEnemy.h"
#include "../../Engine/Implementation/DXMathHelper.h"

IEnemy::IEnemy() : CurrentTexture(nullptr), Shader(nullptr)
{
	AttackTimer = AttackCooldown;
}

IEnemy::IEnemy(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy) : CurrentTexture(RenderableIn), Shader(ShaderIn)
{
	switch (Enemy)
	{
	case FastPack:
		SetStats(5, 5, 10, 0.5, false);
		break;
	case SlowGrunts:
		SetStats(25, 5, 2, 1, false);
		break;
	case Flyers:
		SetStats(5, 2, 5, 1, true);
		break;
	default:
		break;
	}
	AttackTimer = AttackCooldown;
}

void IEnemy::Init(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy)
{
	CurrentTexture = RenderableIn;
	Shader = ShaderIn;
	switch (Enemy)
	{
	case FastPack:
		SetStats(5, 5, 10, 0.5, false);
		break;
	case SlowGrunts:
		SetStats(25, 5, 2, 1, false);
		break;
	case Flyers:
		SetStats(5, 2, 5, 1, true);
		break;
	default:
		break;
	}
	AttackTimer = AttackCooldown;
}

void IEnemy::Register(IGraphics* Graphics)
{
	Graphics->AddSpriteToRender(Shader, CurrentTexture);
}

void IEnemy::Unregister(IGraphics* Graphics)
{
	Graphics->RemoveSpriteFromRender(Shader, CurrentTexture);
}

float IEnemy::GetHealth()
{
	return Health;
}

void IEnemy::DamageEntity(float Amount)
{
	Health -= Amount;
}

DirectX::XMFLOAT2 IEnemy::GetPosition()
{
	return Position;
}

void IEnemy::SetPosition(DirectX::XMFLOAT2 PositionIn)
{
	Position = PositionIn;
}

void IEnemy::Update(float DeltaTime)
{
	if (Target != nullptr)
	{
		MoveTowardsTarget(DeltaTime);
	}
}

void IEnemy::MoveTowardsTarget(float DeltaTime)
{
	DirectX::XMFLOAT2 Distance = DXHelper::Subtract(Target->GetPosition(), Position);
	DirectX::XMFLOAT2 UnitDistance = DXHelper::Normalise(Distance);

	if (DXHelper::Magnitude(Distance) < 10.0f)
	{
		Position = DXHelper::Multiply(DXHelper::Add(UnitDistance, Position), (Speed * DeltaTime));
	}
	else
	{
		AttackTimer -= DeltaTime;
		if (AttackTimer < 0)
		{
			AttackTimer = AttackCooldown;
			Target->DamageEntity(Damage);
		}
	}
}

void IEnemy::SetStats(float HealthIn, float DamageIn, float SpeedIn, float AttackCooldownIn, bool bCanFly)
{
	Health = HealthIn;
	Damage = DamageIn;
	Speed = SpeedIn;
	AttackCooldown = AttackCooldownIn;
	bFlying = bCanFly;
}
