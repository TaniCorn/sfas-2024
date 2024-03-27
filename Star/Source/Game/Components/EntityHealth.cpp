#include "EntityHealth.h"

EntityHealth::EntityHealth(float HealthIn) : Health(HealthIn), MaxHealth(HealthIn)
{
}

void EntityHealth::SetEntityHealth(float HealthIn) 
{
	Health = HealthIn;
	MaxHealth = HealthIn;
}

void EntityHealth::DamageEntity(float Amount)
{
	Health -= Amount;
	if (Health < 0)
	{
		Health = 0;
	}
}

const float EntityHealth::GetMaxHealth() const
{
	return MaxHealth;
}
