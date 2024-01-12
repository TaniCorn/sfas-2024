#pragma once
#include "TowerPlot.h"
#include <vector>
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
	Interactable Interact;
	std::vector<TowerPlot*> Plots;
private:
	IShader* Shader;
	IRenderable* Renderable;
	DirectX::XMFLOAT2 Position;

	float RotationSpeed = 5;
};

