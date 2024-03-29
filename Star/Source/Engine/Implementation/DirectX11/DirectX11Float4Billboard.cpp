#include "DirectX11Float4Billboard.h"

#include <D3DCompiler.h>
#include "DirectX11Graphics.h"

DirectX11Float4Billboard::DirectX11Float4Billboard(ID3D11DeviceContext* ContextIn, ID3D11Buffer* VertexBufferIn, unsigned int vertexStride, unsigned int vertexOffset, unsigned int vertexCountIn, ITexture* TextureIn, ID3D11Buffer* pixelBufferIn, float* ParamPtr) : IRenderable(TextureIn), Context(ContextIn), VertexBuffer(VertexBufferIn), vertexStride(vertexStride), vertexOffset(vertexOffset), vertexCount(vertexCountIn), PixelBuffer(pixelBufferIn)
{
	Params = ParamPtr;
}

DirectX11Float4Billboard::~DirectX11Float4Billboard()
{
	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}
	if (PixelBuffer)
	{
		PixelBuffer->Release();
		PixelBuffer = nullptr;
	}
}

void DirectX11Float4Billboard::Update(ID3D11DeviceContext* ContextIn)
{
	if (Params)
	{
		//Dynamic resource
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		Float4Param* fadePtr;
		result = ContextIn->Map(PixelBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		fadePtr = (Float4Param*)mappedResource.pData;
		fadePtr->x = Params[0];
		fadePtr->y = Params[1];
		fadePtr->z = Params[2];
		fadePtr->w = Params[3];
		ContextIn->Unmap(PixelBuffer, 0);

	}
	if (ContextIn)
	{
		if (Texture)
		{
			Texture->Update();
		}
		ContextIn->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ContextIn->IASetVertexBuffers(0, 1, &VertexBuffer, &vertexStride, &vertexOffset);
		ContextIn->PSSetConstantBuffers(1, 1, &PixelBuffer);
		ContextIn->Draw(vertexCount, 0);
	}
}

void DirectX11Float4Billboard::BindParam(float* Param)
{
	Params = Param;
}
