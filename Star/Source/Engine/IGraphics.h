
#pragma once

#include <map>
#include <list>
#include <set>
#include <string>

class IRenderable;
class IShader;
class ITexture;
class IText;
class UIObject;

class IGraphics
{
public:

	IGraphics();
	virtual ~IGraphics();

	virtual void Update() = 0;
	virtual bool IsValid() = 0;

	virtual ITexture* CreateTexture(const wchar_t* filepath, std::string identifierName) = 0;
	virtual IShader* CreateShader(const wchar_t* filepath, const char* vsentry, const char* vsshader, const char* psentry, const char* psshader) = 0;
	virtual IText* CreateText(const char* text, float positionX = 0, float positionY = 0, float scaleX = 1, float scaleY = 1, float rotation = 0, float r = 1, float g = 1, float b = 1, float a = 1) = 0;
	virtual IRenderable* CreateBillboard(IShader* ShaderIn, ITexture* TextureIn) = 0;
	virtual IRenderable* CreateFloat4Billboard(IShader* ShaderIn, ITexture* TextureIn, float* ParamPtr) = 0;
	virtual void Cleanup();

	ITexture* GetTexture(std::string identifierName);
	void AddSpriteToRender(IShader* ShaderIn, IRenderable* RenderableIn);
	void RemoveSpriteFromRender(IShader* ShaderIn, IRenderable* RenderableIn);
	void AddUIToRender(IShader* ShaderIn, IRenderable* RenderableIn);
	void RemoveUIFromRender(IShader* ShaderIn, IRenderable* RenderableIn);
	void AddText(IText* TextIn);
	void RemoveText(IText* TextIn);
	virtual float GetWindowWidth() = 0;
	virtual float GetWindowHeight() = 0;
protected:
	std::map<IShader*, std::list<IRenderable*> > Renderables;
	std::map<std::string, ITexture*> Textures;

	std::list<IText*> UIText;
	std::map<IShader*, std::list<IRenderable*> > UIRenderables;

	std::set<ITexture*> TexturesRegister;
	std::set<IShader*> ShadersRegister;
	std::set<IRenderable*> RenderablesRegister;
	std::set<IText*> TextRegister;


};

