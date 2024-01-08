
#pragma once

class ITexture;
class ID3D11DeviceContext;

class IShader
{
public:

	IShader(ITexture* TextureIn);
	virtual ~IShader();
	virtual void Update() = 0;
	virtual void SetTexture(ITexture* TextureIn);
	const ITexture* GetTexture() const;

protected: 

	ITexture* Texture;

};

