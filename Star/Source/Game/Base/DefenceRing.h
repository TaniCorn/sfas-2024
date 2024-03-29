#pragma once

#include "../../Engine/IRegisteredObject.h"
#include "TowerPlot.h"
#include "../Towers/Tower.h"
#include <map>
#include <vector>
#include <memory>
class Enemy;


class DefenceRing : public IRegisteredObject
{
public:
	DefenceRing(IShader* ShaderIn, IRenderable* RenderableIn);
	virtual void Register(IGraphics* GraphicsIn) override;
	virtual void Unregister(IGraphics* GraphicsIn) override;
	
	DirectX::XMFLOAT2 GetPosition() const;
	bool IsPlotAvailable() const;

	void Rotate(float Direction, float DeltaTime);
	void Update(float DeltaTime, const std::vector<Enemy*>& Enemies);
	void PlantTower(std::unique_ptr<Tower> TowerIn);
	void PlantPlot(std::unique_ptr<TowerPlot> PlotIn);
	void SetPosition(const DirectX::XMFLOAT2 Location);
	void SetScale(const float x, const float y);
	void BindPlotsColor();

	Interactable Interact;
private:
	IShader* Shader;
	IRenderable* Renderable;
	DirectX::XMFLOAT2 Position;
	std::map<std::unique_ptr<TowerPlot>, std::unique_ptr<Tower>> PlotsAndTowers;

	const float RotationSpeed = 5;
};

