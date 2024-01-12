#include "DefenceRing.h"
#include "../../Engine/IRenderable.h"
constexpr float Pie = 3.14159265359f;
constexpr float TwoPies = Pie * 2.0f;

DefenceRing::DefenceRing(IShader* ShaderIn, IRenderable* RenderableIn) : Shader(ShaderIn), Renderable(RenderableIn)
{
	Interact.SetHighlightColor(1, 1, 1, 1);
	Interact.SetNormalColor(0.7, 0.7, 0.8, 1);
	Interact.Unhighlighted();
	RenderableIn->BindParam(Interact.GetColorBind());
}

void DefenceRing::Register(IGraphics* GraphicsIn)
{
	GraphicsIn->AddSpriteToRender(Shader, Renderable);
}

void DefenceRing::Unregister(IGraphics* GraphicsIn)
{
	GraphicsIn->RemoveSpriteFromRender(Shader, Renderable);
}

void DefenceRing::SetPosition(DirectX::XMFLOAT2 Location)
{
	Position = Location;
	Renderable->SetPosition(Location.x, Location.y);
}

DirectX::XMFLOAT2 DefenceRing::GetPosition() const
{
	return Position;
}

void DefenceRing::SetScale(float x, float y)
{
	Renderable->SetScale(x, y);
}

void DefenceRing::Rotate(float Direction, float DeltaTime)
{
	//Rotate Ring
	float delta = Direction * RotationSpeed * DeltaTime;
	float newRotation = static_cast<float>(fmod(Renderable->GetTransform().Rotation + delta, TwoPies));
	Renderable->SetRotation(newRotation);

	delta = -Direction * RotationSpeed * DeltaTime;
	//Rotate plots around ring
	for (int i = 0; i < Plots.size(); i++)
	{
		//TODO: Find out if the rotation goes between 0 and 360,
		//if not we need to convert it
		float newOutRotation = static_cast<float>(fmod(Plots[i]->Rotation + delta, TwoPies));
		int y = (cos(newOutRotation) * (Plots[i]->DistanceFromCenter));
		int x = (sin(newOutRotation) * (Plots[i]->DistanceFromCenter));
		Plots[i]->SetPosition(DirectX::XMFLOAT2(x, y));
		Plots[i]->Rotation = newOutRotation;
	}

}

bool DefenceRing::PlotAvailable()
{
	for (int i = 0; i < Plots.size(); i++)
	{
		if (Plots[i]->IsAvailable())
		{
			return true;
		}
	}
	return false;
}

void DefenceRing::PlantTower(Tower* TowerIn)
{
	std::vector<TowerPlot*> PlotsAvailable;
	for (int i = 0; i < Plots.size(); i++)
	{
		if (Plots[i]->IsAvailable())
		{
			PlotsAvailable.push_back(Plots[i]);
		}
	}
	int PlotNumber = rand() % PlotsAvailable.size();
	PlotsAvailable[PlotNumber]->PlantTower(TowerIn);
}
