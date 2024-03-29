#pragma once

#include "Engine/IGraphics.h"
#include "Engine/Transform2D.h"
#include <Windows.h>
#include <d3dcommon.h>
#include <DirectXMath.h>
#include <string>
#include <SpriteBatch.h>
#include <SpriteFont.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11Buffer;
struct ID3D11BlendState;
enum D3D_FEATURE_LEVEL;

class DirectX11Graphics : public IGraphics
{
public:

	DirectX11Graphics(HWND hwndIn);
	virtual ~DirectX11Graphics();

	virtual void Update();
	virtual bool IsValid();

	virtual ITexture* CreateTexture(const wchar_t* filepath, std::string identifierName);
	virtual IText* CreateText(const char* text, float positionX = 0, float positionY = 0, float scaleX = 1, float scaleY = 1, float rotation = 0, float r = 255, float g = 255, float b = 255, float a = 255);
	virtual IShader* CreateShader(const wchar_t* filepath, const char* vsentry, const char* vsshader, const char* psentry, const char* psshader);
	virtual IRenderable* CreateBillboard(IShader* ShaderIn, ITexture* TextureIn);
	virtual IRenderable* CreateFloat4Billboard(IShader* ShaderIn, ITexture* TextureIn, float* ParamPtr);

	ID3D11Device* GetDevice() const { return Device; }
	ID3D11DeviceContext* GetContext() const { return Context; }

	virtual float GetWindowWidth();
	virtual float GetWindowHeight();

protected:

	virtual void SetWorldMatrix(const Transform2D& transform);
	virtual bool CompileShader(LPCWSTR filepath, LPCSTR entry, LPCSTR shader, ID3DBlob** buffer);

private:

	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
	IDXGISwapChain* SwapChain;
	ID3D11RenderTargetView* BackbufferView;
	ID3D11Texture2D* BackbufferTexture;
	ID3D11BlendState* BlendState;
	ID3D11Buffer* Mvp;
	DirectX::XMMATRIX vpMatrix;
	D3D_FEATURE_LEVEL FeatureLevel;
	HWND hwnd;
	int width;
	int height;

	DirectX::SpriteBatch* SpriteBatch;
	DirectX::SpriteFont* SpriteFont;

};

