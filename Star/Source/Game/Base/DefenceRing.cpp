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
	
	for (auto it = PlotsAndTowers.begin(); it != PlotsAndTowers.end(); it++)
	{
		float newOutRotation = it->first->Rotation + (delta * RotationSpeed * 5);
		float radRot = newOutRotation * Pie / 180;
		int y = (cos(radRot) * (it->first->DistanceFromCenter));
		int x = (sin(radRot) * (it->first->DistanceFromCenter));
		it->first->SetPosition(DirectX::XMFLOAT2(x, y));
		it->first->Rotation = newOutRotation;
		if (!it->first->IsAvailable())
		{
			it->second->SetPosition(it->first->GetPosition());
		}
	}

}

bool DefenceRing::PlotAvailable()
{
	for (auto it = PlotsAndTowers.begin(); it != PlotsAndTowers.end(); it++)
	{
		if (it->first->IsAvailable())
		{
			return true;
		}
	}
	return false;
}

void DefenceRing::PlantTower(std::unique_ptr<Tower> TowerIn)
{
	std::vector<std::map<std::unique_ptr<TowerPlot>, std::unique_ptr<Tower>>::iterator> PlotsAvailable;
	for (auto it = PlotsAndTowers.begin(); it != PlotsAndTowers.end(); it++)
	{
		if (it->first->IsAvailable())
		{
			PlotsAvailable.push_back(it);
		}
	}
	int PlotNumber = rand() % PlotsAvailable.size();
	auto PlotIt = PlotsAvailable[PlotNumber];
	PlotIt->second = std::move(TowerIn);
	PlotIt->first->PlantTower();
	PlotIt->second->SetPosition(PlotIt->first->GetPosition());
}

void DefenceRing::BindPlotsColor()
{
	Interact.SetNormalColor(1.0, 1.0, 1.0, 0.8);
	Interact.SetHighlightColor(0.6, 1, 0.6, 0.9);
	Interact.Unhighlighted();
	for (auto it = PlotsAndTowers.begin(); it != PlotsAndTowers.end(); it++)
	{
		it->first->GetRenderable()->BindParam(Interact.GetColorBind());
		if (!it->first->IsAvailable())
		{
			it->second->GetRenderable()->BindParam(Interact.GetColorBind());
		}
	}
}

void DefenceRing::Update(float DeltaTime, const std::vector<Enemy*>& Enemies)
{
	for (auto it = PlotsAndTowers.begin(); it != PlotsAndTowers.end(); it++)
	{
		if (!it->first->IsAvailable())
		{
			it->second->Update(DeltaTime);
			it->second->AttackUpdate(Enemies);
		}
	}
}


