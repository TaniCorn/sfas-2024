#pragma once
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../Components/ColorHighlighting.h"
#include <DirectXMath.h>

class Tower : public IRegisteredObject
{
	Tower(float Damage, DirectX::XMFLOAT2 Position);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	virtual void SetPosition(DirectX::XMFLOAT2 Location) = 0;
	virtual void Update(float DeltaTime) = 0;

	ColorHighlighting ColorHighlight;
protected:
	IShader* Shader;
	IRenderable* CurrentTexture;

	float Damage;
	DirectX::XMFLOAT2 Position;

};

