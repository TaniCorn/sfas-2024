#pragma once

#include "Engine/IRenderable.h"
#include <d3d11.h>
#include <DirectXMath.h>

class DirectX11Graphics;


class DirectX11Fade : public IRenderable
{
public:

	DirectX11Fade(ID3D11DeviceContext* ContextIn, ID3D11Buffer* VertexBufferIn, unsigned int vertexStride, unsigned int vertexOffset, unsigned int vertexCountIn, ID3D11Buffer* pixelBufferIn, float* ParamPtr);
	virtual ~DirectX11Fade();
	virtual void Update(ID3D11DeviceContext* Context);


private:

	ID3D11DeviceContext* Context;
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* PixelBuffer;
	unsigned int vertexStride;
	unsigned int vertexOffset;
	unsigned int vertexCount;

	float* Params;
	struct FadeBuffer {
		float FadeTime;
		float r, g, b;
	};
	FadeBuffer Fade;
};

