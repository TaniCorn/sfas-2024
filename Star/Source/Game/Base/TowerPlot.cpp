#include "TowerPlot.h"
#include "../../Engine/IRenderable.h"
TowerPlot::TowerPlot(IShader* ShaderIn, IRenderable* RenderableIn) : Shader(ShaderIn), Renderable(RenderableIn), Position(0, 0)
{
}

void TowerPlot::Register(IGraphics* GraphicsIn)
{
	GraphicsIn->AddSpriteToRender(Shader, Renderable);
}

void TowerPlot::Unregister(IGraphics* GraphicsIn)
{
	GraphicsIn->RemoveSpriteFromRender(Shader, Renderable);
}

void TowerPlot::SetPosition(DirectX::XMFLOAT2 Location)
{
	Position = Location;
	Renderable->SetPosition(Location.x, Location.y);
}

DirectX::XMFLOAT2 TowerPlot::GetPosition() const
{
	return Position;
}

void TowerPlot::SetScale(float x, float y)
{
	Renderable->SetScale(x, y);
}
