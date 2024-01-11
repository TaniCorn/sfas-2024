#include "DirectX11Shader.h"
#include "DirectX11Texture.h"


DirectX11Shader::DirectX11Shader(ID3D11DeviceContext* ContextIn, ID3D11VertexShader* VertexShaderIn, ID3D11PixelShader* PixelShaderIn, ID3D11InputLayout* InputLayoutIn) : IShader(), Context(ContextIn), VertexShader(VertexShaderIn), PixelShader(PixelShaderIn), InputLayout(InputLayoutIn) 
{
}

DirectX11Shader::~DirectX11Shader()
{
	if (InputLayout)
	{
		InputLayout->Release();
		InputLayout = nullptr;
	}

	if (VertexShader)
	{
		VertexShader->Release();
		VertexShader = nullptr;
	}

	if (PixelShader)
	{
		PixelShader->Release();
		PixelShader = nullptr;
	}
}

void DirectX11Shader::Update()
{
	if (Context)
	{
		Context->IASetInputLayout(InputLayout);
		Context->VSSetShader(VertexShader, 0, 0);
		Context->PSSetShader(PixelShader, 0, 0);

	}
}