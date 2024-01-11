#pragma once

#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
class IEnemy : public IRegisteredObject
{
public:
	virtual void Register(IGraphics* GraphicsIn) = 0;
	virtual void Unregister(IGraphics* GraphicsIn) = 0;


	float Health;
	float Speed;
	float Damage;
	bool Flying;
};

