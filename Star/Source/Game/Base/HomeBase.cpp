#include "HomeBase.h"
#include "../Components/ColorHighlighting.h"


HomeBase::HomeBase(IRenderable* RenderableIn, IShader* ShaderIn) : CurrentTexture(RenderableIn), Shader(ShaderIn), Health(50), ColorHighlight()
{
}


void HomeBase::Register(IGraphics* Graphics)
{
	Graphics->AddSpriteToRender(Shader, CurrentTexture);
}

void HomeBase::Unregister(IGraphics* Graphics)
{
	Graphics->RemoveSpriteFromRender(Shader, CurrentTexture);
}

void HomeBase::DamageEntity(float Amount)
{
	Health.DamageEntity(Amount);
	//Update Health UI
	ColorHighlight.Highlighted();
}

void HomeBase::Update(float DeltaTime)
{
	ColorHighlight.Update(DeltaTime);
}

void HomeBase::SetPosition(DirectX::XMFLOAT2 Location)
{
	Position = Location;
	CurrentTexture->SetPosition(Location.x, Location.y);
}


