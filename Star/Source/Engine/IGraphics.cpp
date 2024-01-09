#include "IGraphics.h"
#include "ITexture.h"
#include "IShader.h"
#include "IRenderable.h"


IGraphics::IGraphics() : Renderables()
{
}

IGraphics::~IGraphics()
{
    for (auto bucket = Renderables.begin(); bucket != Renderables.end(); ++bucket)
    {
        for (auto renderable = bucket->second.begin(); renderable != bucket->second.end(); ++renderable)
        {
            delete (*renderable);
        }
        
        delete bucket->first;
    }

    Renderables.clear();

    for (auto texture = Textures.begin(); texture != Textures.end(); ++texture)
    {
        delete (texture->second);
    }

    Textures.clear();
}

void IGraphics::AddText(IText* TextIn)
{
    Text.push_back(TextIn);
}

void IGraphics::RemoveText(IText* TextIn)
{
    Text.remove(TextIn);
}

void IGraphics::Cleanup()
{
    for (auto bucket = Renderables.begin(); bucket != Renderables.end(); ++bucket)
    {
        for (auto renderable = bucket->second.begin(); renderable != bucket->second.end(); ++renderable)
        {
            delete (*renderable);
        }

        delete bucket->first;
    }

    Renderables.clear();

    for (auto texture = Textures.begin(); texture != Textures.end(); ++texture)
    {
         delete (texture->second);
    }

    Textures.clear();
}
