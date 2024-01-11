
#pragma once

class ITexture;
class ID3D11DeviceContext;

class IShader
{
public:

	IShader();
	virtual ~IShader();
	virtual void Update() = 0;

};

