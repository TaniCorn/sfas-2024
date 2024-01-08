#include "IShader.h"
#include "ITexture.h"

IShader::IShader(ITexture* TextureIn) : Texture(TextureIn)
{
}

IShader::~IShader()
{
    //Don't delete Texture, Texture should handle itself
}

void IShader::SetTexture(ITexture* TextureIn)
{
    Texture = TextureIn;
}

const ITexture* IShader::GetTexture() const
{
    return Texture;
}
