#include "DirectX11Billboard.h"

#include <D3DCompiler.h>
#include "DirectX11Graphics.h"

DirectX11Billboard::DirectX11Billboard(ID3D11DeviceContext* ContextIn, ID3D11Buffer* VertexBufferIn, unsigned int vertexStride, unsigned int vertexOffset, unsigned int vertexCountIn, ITexture* TextureIn) : IRenderable(TextureIn), Context(ContextIn), VertexBuffer(VertexBufferIn), vertexStride(vertexStride), vertexOffset(vertexOffset), vertexCount(vertexCountIn)
{
}

DirectX11Billboard::~DirectX11Billboard()
{
	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}
}
	
void DirectX11Billboard::Update(ID3D11DeviceContext* ContextIn)
{
	if (ContextIn)
	{
		if (Texture)
		{
			Texture->Update();
		}
		ContextIn->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ContextIn->IASetVertexBuffers(0, 1, &VertexBuffer, &vertexStride, &vertexOffset);
		ContextIn->Draw(vertexCount, 0);
	}
}

void DirectX11Billboard::BindParam(float* Param)
{
}
