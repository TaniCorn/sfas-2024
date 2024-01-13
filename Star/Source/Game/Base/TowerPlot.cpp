#include "TowerPlot.h"
#include "../../Engine/IRenderable.h"
#include "../Towers/Tower.h"
TowerPlot::TowerPlot(IShader* ShaderIn, IRenderable* RenderableIn) : Shader(ShaderIn), Renderable(RenderableIn), Position(0, 0)
{
	RenderableIn->BindParam(Interact.GetColorBind());
}

TowerPlot::~TowerPlot()
{
	if (PlantedTower != nullptr)
	{
		delete PlantedTower;
		PlantedTower = nullptr;
	}
}

void TowerPlot::Register(IGraphics* GraphicsIn)
{
	GraphicsIn->AddSpriteToRender(Shader, Renderable, 1);
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

bool TowerPlot::IsAvailable()
{
	if (PlantedTower == nullptr)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void TowerPlot::PlantTower(Tower* TowerToPlant)
{
	PlantedTower = TowerToPlant;
	TowerToPlant->LinkPosition(Position);
	Interact.SetNormalColor(0, 0, 0, 0);
	Interact.Unhighlighted();
}

IRenderable* TowerPlot::GetRenderable()
{
	return Renderable;
}

IRenderable* TowerPlot::GetTowerRenderable()
{
	if (PlantedTower != nullptr)
	{
		return PlantedTower->GetRenderable();
	}
	return nullptr;
}
