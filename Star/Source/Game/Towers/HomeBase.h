#pragma once

#include "../EntityHealth.h"
#include "../../Engine/IRenderable.h"
#include "../../Engine/IRegisteredObject.h"
#include "../../../ColorHighlighting.h"
#include <DirectXMath.h>
class ColorHighlighting;

class HomeBase : public IRegisteredObject
{
public:
	HomeBase(IRenderable* RenderableIn, IShader* ShaderIn);
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	virtual void DamageEntity(float Amount);
	void Update(float DeltaTime);
	void SetPosition(DirectX::XMFLOAT2 Location);

	EntityHealth Health;
	ColorHighlighting ColorHighlight;
	DirectX::XMFLOAT2 Position;
protected:
	IShader* Shader;
	IRenderable* CurrentTexture;
	

};

