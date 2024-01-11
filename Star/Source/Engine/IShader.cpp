#include "IShader.h"
#include "ITexture.h"

IShader::IShader()
{
}

IShader::~IShader()
{
    //Don't delete Texture, Texture should handle itself
}

