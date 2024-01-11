#include "IGraphics.h"
#include "ITexture.h"
#include "IShader.h"
#include "IRenderable.h"
#include <set>


IGraphics::IGraphics() : Renderables(), UIRenderables()
{
}

IGraphics::~IGraphics()
{
    for (auto it = RenderablesRegister.begin(); it != RenderablesRegister.end(); ++it)
    {
        delete* it;
    }
    for (auto it = ShadersRegister.begin(); it != ShadersRegister.end(); ++it)
    {
        delete* it;
    }
    for (auto it = TextRegister.begin(); it != TextRegister.end(); ++it)
    {
        delete* it;
    }
    for (auto it = TexturesRegister.begin(); it != TexturesRegister.end(); ++it)
    {
        delete* it;
    }
    RenderablesRegister.clear();
    ShadersRegister.clear();
    TextRegister.clear();
    TexturesRegister.clear();
    Renderables.clear();
    UIRenderables.clear();
    Textures.clear();
    UIText.clear();
}

void IGraphics::AddText(IText* TextIn)
{
    UIText.push_back(TextIn);
    TextRegister.insert(TextIn);
}

void IGraphics::RemoveText(IText* TextIn)
{
    UIText.remove(TextIn);
}
ITexture* IGraphics::GetTexture(std::string identifierName)
{
    return Textures[identifierName];
}

void IGraphics::AddSpriteToRender(IShader* ShaderIn, IRenderable* RenderableIn)
{
    Renderables[ShaderIn].push_back(RenderableIn);
    ShadersRegister.insert(ShaderIn);
    RenderablesRegister.insert(RenderableIn);
}

void IGraphics::RemoveSpriteFromRender(IShader* ShaderIn, IRenderable* RenderableIn)
{
    Renderables[ShaderIn].remove(RenderableIn);
}

void IGraphics::AddUIToRender(IShader* ShaderIn, IRenderable* RenderableIn)
{
    UIRenderables[ShaderIn].push_back(RenderableIn);
    ShadersRegister.insert(ShaderIn);
    RenderablesRegister.insert(RenderableIn);
}

void IGraphics::RemoveUIFromRender(IShader* ShaderIn, IRenderable* RenderableIn)
{
    UIRenderables[ShaderIn].remove(RenderableIn);
}

void IGraphics::Cleanup()
{
    for (auto it = RenderablesRegister.begin(); it != RenderablesRegister.end(); ++it)
    {
        delete *it;
    }    
    for (auto it = ShadersRegister.begin(); it != ShadersRegister.end(); ++it)
    {
        delete* it;
    }
    for (auto it = TextRegister.begin(); it != TextRegister.end(); ++it)
    {
        delete* it;
    }
    for (auto it = TexturesRegister.begin(); it != TexturesRegister.end(); ++it)
    {
        delete* it;
    }
    RenderablesRegister.clear();
    ShadersRegister.clear();
    TextRegister.clear();
    TexturesRegister.clear();
    Renderables.clear();
    UIRenderables.clear();
    Textures.clear();
    UIText.clear();
}
