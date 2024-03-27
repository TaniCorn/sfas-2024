#pragma once
#include "TowerPlot.h"
#include <vector>
#include <memory>
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
	void PlantTower(Tower* TowerIn);
	void BindPlotsColor();
	Interactable Interact;
	std::vector<std::unique_ptr<TowerPlot>> Plots;
private:
	IShader* Shader;
	IRenderable* Renderable;
	DirectX::XMFLOAT2 Position;

	float RotationSpeed = 5;
};

