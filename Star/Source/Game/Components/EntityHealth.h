#pragma once

class EntityHealth 
{
public:
	EntityHealth(float HealthIn);
	void SetEntityHealth(float HealthIn);
	void DamageEntity(float Amount);
	const float GetMaxHealth();

	float Health;
private:
	float MaxHealth;

};

