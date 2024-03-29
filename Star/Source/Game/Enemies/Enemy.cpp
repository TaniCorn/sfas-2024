#include "Enemy.h"
#include "../../Engine/Implementation/DXMathHelper.h"
DirectX::XMFLOAT2 Enemy::TargetPosition = DirectX::XMFLOAT2(0, 0);
EntityHealth* Enemy::TargetHealthObject = nullptr;


Enemy::Enemy() : CurrentTexture(nullptr), Shader(nullptr), ColorHighlight(), Health(0)
{
}

Enemy::Enemy(IRenderable* RenderableIn, IShader* ShaderIn, EnemyTypes Enemy) : CurrentTexture(RenderableIn), Shader(ShaderIn), ColorHighlight(), Health(0)
{
	switch (Enemy)
	{
	case EnemyTypes::FastPacks:
		SetStats(5, 5, 50, 2, false);
		break;
	case EnemyTypes::SlowGrunts:
		SetStats(20, 5, 20, 10, false);
		break;
	case EnemyTypes::Flyers:
		SetStats(5, 2, 40, 3, true);
		break;
	default:
		break;
	}

	//Sets the enemy to invisibble and dead when spawning
	bAlive = false;
	SetPosition(DirectX::XMFLOAT2(0, 0));
	ColorHighlight.SetNormalColor(0, 0, 0, 0);
}

void Enemy::Register(IGraphics* Graphics)
{
	Graphics->AddSpriteToRender(Shader, CurrentTexture, 4);
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

void Enemy::Spawn(const DirectX::XMFLOAT2 Location)
{
	SetPosition(Location);
	bAlive = true;
	Health.Health = Health.GetMaxHealth();
	ColorHighlight.SetNormalColor(1, 1, 1, 1);
	ColorHighlight.Unhighlighted();
}

void Enemy::Update(float DeltaTime)
{
	ColorHighlight.Update(DeltaTime);
	if (TargetHealthObject != nullptr && bAlive)
	{
		MoveTowardsTarget(DeltaTime);
	}
}

void Enemy::SetPosition(DirectX::XMFLOAT2 Location)
{
	Position = Location;
	CurrentTexture->SetPosition(Location.x, Location.y);
}

void Enemy::SetRotation(float Rotation)
{
	CurrentTexture->SetRotation(Rotation);
}

DirectX::XMFLOAT2 Enemy::GetPosition() const
{
	return Position;
}

int Enemy::GetGoldGain() const
{
	return GoldGain;
}
void Enemy::MoveTowardsTarget(float DeltaTime)
{
	DirectX::XMFLOAT2 Vector = DXHelper::Subtract(TargetPosition, Position);
	float Distance = DXHelper::Magnitude(Vector);

	if (Distance > 10.0f)
	{
		MoveAndRotate(DeltaTime, Vector);
	}
	else
	{
		TargetHealthObject->DamageEntity(Damage);
		DamageEntity(Health.GetMaxHealth());
	}
}

void Enemy::MoveAndRotate(float DeltaTime, DirectX::XMFLOAT2 Direction)
{
	DirectX::XMFLOAT2 UnitVector = DXHelper::Normalise(Direction);
	DirectX::XMFLOAT2 Direction = DXHelper::Multiply(UnitVector, (Speed * DeltaTime));

	//Move
	SetPosition(DXHelper::Add(Direction, Position));

	//Rotate
	float RadRotDot = acos(DXHelper::DotProduct(DirectX::XMFLOAT2(0, -1), UnitVector));
	if (UnitVector.x < 0)
	{
		SetRotation(-RadRotDot);
	}
	else
	{
		SetRotation(RadRotDot);
	}
}

void Enemy::SetStats(const float HealthIn, const float DamageIn, const float SpeedIn, const int Gold, const bool bCanFly)
{
	Health.SetEntityHealth(HealthIn);
	Damage = DamageIn;
	Speed = SpeedIn;
	bFlying = bCanFly;
	GoldGain = Gold;
}
