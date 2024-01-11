#include "DirectX11Fade.h"

#include <D3DCompiler.h>
#include "DirectX11Graphics.h"

DirectX11Fade::DirectX11Fade(ID3D11DeviceContext* ContextIn, ID3D11Buffer* VertexBufferIn, unsigned int vertexStride, unsigned int vertexOffset, unsigned int vertexCountIn, ITexture* TextureIn, ID3D11Buffer* pixelBufferIn, float* ParamPtr) : IRenderable(TextureIn), Context(ContextIn), VertexBuffer(VertexBufferIn), vertexStride(vertexStride), vertexOffset(vertexOffset), vertexCount(vertexCountIn), PixelBuffer(pixelBufferIn)
{
	Fade.FadeTime = 0;
	Fade.r = 1;
	Fade.g = 1;
	Fade.b = 1;
	Params = ParamPtr;
}

DirectX11Fade::~DirectX11Fade()
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

void DirectX11Fade::Update(ID3D11DeviceContext* Context)
{
	if (Params)
	{
		Fade.FadeTime = Params[3];
		Fade.r = Params[0];
		Fade.g = Params[1];
		Fade.b = Params[2];

		//Dynamic resource
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		FadeBuffer* fadePtr;
		result = Context->Map(PixelBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		fadePtr = (FadeBuffer*)mappedResource.pData;
		fadePtr->FadeTime = Fade.FadeTime;
		fadePtr->r = Fade.r;
		fadePtr->g = Fade.g;
		fadePtr->b = Fade.b;
		Context->Unmap(PixelBuffer, 0);
		//Context->UpdateSubresource(PixelBuffer, 0, 0, &Fade, 0, 0); // Not recommended for dynamic resources

	}
	if (Context)
	{
		if (Texture)
		{
			Texture->Update();
		}
		Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Context->IASetVertexBuffers(0, 1, &VertexBuffer, &vertexStride, &vertexOffset);
		Context->PSSetConstantBuffers(1, 1, &PixelBuffer);
		Context->Draw(vertexCount, 0);
	}
}