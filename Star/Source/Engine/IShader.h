
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


//Unfortunately writing shaders that have variables attached to them in an efficient way would require us to unnatatch it from the Graphics creation pipeline
//So for now we must continue doing all the usual steps and creating a new function in the graphics pipleine for each shader. 
//The parameters must also be updated via referencing rather than a functino call

