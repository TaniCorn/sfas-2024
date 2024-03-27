#pragma once

#include "Engine/IRenderable.h"
#include <d3d11.h>
#include <DirectXMath.h>

class DirectX11Graphics;


class DirectX11Float4Billboard : public IRenderable
{
public:

	DirectX11Float4Billboard(ID3D11DeviceContext* ContextIn, ID3D11Buffer* VertexBufferIn, unsigned int vertexStride, unsigned int vertexOffset, unsigned int vertexCountIn, ITexture* TextureIn, ID3D11Buffer* pixelBufferIn, float* ParamPtr);
	virtual ~DirectX11Float4Billboard();
	virtual void Update(ID3D11DeviceContext* ContextIn);
	virtual void BindParam(float* Param);

private:

	ID3D11DeviceContext* Context;
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* PixelBuffer;
	unsigned int vertexStride;
	unsigned int vertexOffset;
	unsigned int vertexCount;

	float* Params;
	struct Float4Param {
		float x,y,z,w;
	};
};

