#include "Enemy.h"
#include "../../Engine/Implementation/DXMathHelper.h"

Enemy::Enemy() : CurrentTexture(nullptr), Shader(nullptr), ColorHighlight(), Health(0)
{
	AttackTimer = AttackCooldown;
}

Enemy::Enemy(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy) : CurrentTexture(RenderableIn), Shader(ShaderIn), Health(0)
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

void Enemy::Init(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy)
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

void Enemy::Register(IGraphics* Graphics)
{
	Graphics->AddSpriteToRender(Shader, CurrentTexture);
}

void Enemy::Unregister(IGraphics* Graphics)
{
	Graphics->RemoveSpriteFromRender(Shader, CurrentTexture);
}

void Enemy::DamageEntity(float Amount)
{
	Health.DamageEntity(Amount);
	ColorHighlight.Highlighted();
}

void Enemy::Update(float DeltaTime)
{
	ColorHighlight.Update(DeltaTime);
	if (Target != nullptr)
	{
		MoveTowardsTarget(DeltaTime);
	}
}

void Enemy::MoveTowardsTarget(float DeltaTime)
{
	DirectX::XMFLOAT2 Distance = DXHelper::Subtract(TargetPosition, Position);
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

void Enemy::SetStats(float HealthIn, float DamageIn, float SpeedIn, float AttackCooldownIn, bool bCanFly)
{
	Health.SetEntityHealth(HealthIn);
	Damage = DamageIn;
	Speed = SpeedIn;
	AttackCooldown = AttackCooldownIn;
	bFlying = bCanFly;
}
