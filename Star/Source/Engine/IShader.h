
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
	//TODO: Optimise Shading by assigning a Texture to Renderables instead of to shaders. That way 1 shader can be created for any textures, rather than creating a shader per texture
	ITexture* Texture;

};

