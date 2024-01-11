#pragma once
class IGraphics;

class IRegisteredObject
{
public:
	virtual void Register(IGraphics* GraphicsIn) = 0;
	virtual void Unregister(IGraphics* GraphicsIn) = 0;
};

