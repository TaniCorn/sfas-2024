#include "Enemy.h"
#include "../../Engine/Implementation/DXMathHelper.h"
DirectX::XMFLOAT2 Enemy::TargetPosition = DirectX::XMFLOAT2(0, 0);
EntityHealth* Enemy::Target = nullptr;


Enemy::Enemy() : CurrentTexture(nullptr), Shader(nullptr), ColorHighlight(), Health(0)
{
	bAlive = false;
}

void Enemy::Init(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy)
{
	CurrentTexture = RenderableIn;
	Shader = ShaderIn;
	switch (Enemy)
	{
	case FastPack:
		SetStats(5, 5, 60, 0.5, false);
		break;
	case SlowGrunts:
		SetStats(25, 5, 20, 1, false);
		break;
	case Flyers:
		SetStats(5, 2, 45, 1, true);
		break;
	default:
		break;
	}
	SetPosition(DirectX::XMFLOAT2(0, 0));
	bAlive = false;
	ColorHighlight.SetNormalColor(0, 0, 0, 0);
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
	if (Health.Health <= 0)
	{
		bAlive = false;
		ColorHighlight.SetNormalColor(0, 0, 0, 0);
		ColorHighlight.Unhighlighted();
	}
}

bool Enemy::IsAlive() const
{
	return bAlive;
}

bool Enemy::Flying() const
{
	return bFlying;
}

void Enemy::Spawn(DirectX::XMFLOAT2 Location)
{
	SetPosition(Location);
	bAlive = true;
	Health.Health = Health.GetMaxHealth();
	ColorHighlight.SetNormalColor(1, 0, 0, 1);
	ColorHighlight.Unhighlighted();
}

void Enemy::Update(float DeltaTime)
{
	ColorHighlight.Update(DeltaTime);
	if (Target != nullptr && bAlive)
	{
		MoveTowardsTarget(DeltaTime);
	}
}

void Enemy::SetPosition(DirectX::XMFLOAT2 Location)
{
	Position = Location;
	CurrentTexture->SetPosition(Location.x, Location.y);
}

DirectX::XMFLOAT2 Enemy::GetPosition() const
{
	return Position;
}

void Enemy::MoveTowardsTarget(float DeltaTime)
{
	DirectX::XMFLOAT2 Vector = DXHelper::Subtract(TargetPosition, Position);
	DirectX::XMFLOAT2 UnitVector = DXHelper::Normalise(Vector);
	float Distance = DXHelper::Magnitude(Vector);
	if (Distance > 10.0f)
	{
		DirectX::XMFLOAT2 Direction = DXHelper::Multiply(UnitVector, (Speed * DeltaTime));
		SetPosition(DXHelper::Add(Direction, Position));
	}
	else
	{
		Target->DamageEntity(Damage);
		DamageEntity(Health.GetMaxHealth());
	}
}

void Enemy::SetStats(float HealthIn, float DamageIn, float SpeedIn, float AttackCooldownIn, bool bCanFly)
{
	Health.SetEntityHealth(HealthIn);
	Damage = DamageIn;
	Speed = SpeedIn;
	bFlying = bCanFly;
}
