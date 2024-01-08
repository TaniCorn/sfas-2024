
#pragma once

class ITexture
{
public:
	virtual ~ITexture() {};
	virtual void Update() = 0;
	virtual float GetWidth() const = 0;
	virtual float GetHeight() const = 0;

};

