
#pragma once

#include "Engine/IGraphics.h"
#include "Engine/Transform2D.h"
#include "ITexture.h"
class ID3D11DeviceContext;

class IRenderable
{
public:
	IRenderable(ITexture* TextureIn);
	virtual ~IRenderable() {};

	virtual void Update(ID3D11DeviceContext* Context) = 0;
	const Transform2D& GetTransform() const;
	void SetPosition(float x, float y);
	void SetRotation(float r);
	void SetScale(float sx, float sy);
	virtual void SetTexture(ITexture* TextureIn);
	const ITexture* GetTexture() const;
protected:
	ITexture* Texture;
private:
	Transform2D Transform;

};

