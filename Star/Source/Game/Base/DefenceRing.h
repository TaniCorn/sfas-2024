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
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	void SetPosition(DirectX::XMFLOAT2 Location);
	DirectX::XMFLOAT2 GetPosition() const;
	void SetScale(float x, float y);
	void Rotate(float Direction, float DeltaTime);
	bool PlotAvailable();
	void PlantTower(std::unique_ptr<Tower> TowerIn);
	void BindPlotsColor();
	void Update(float DeltaTime, const std::vector<Enemy*>& Enemies);
	Interactable Interact;
	std::map<std::unique_ptr<TowerPlot>,std::unique_ptr<Tower>> PlotsAndTowers;
private:
	IShader* Shader;
	IRenderable* Renderable;
	DirectX::XMFLOAT2 Position;

	float RotationSpeed = 5;
};

