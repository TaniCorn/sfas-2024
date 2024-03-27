#pragma once
#include "../Components/Interactable.h"
#include "../../Engine/IRegisteredObject.h"
#include <DirectXMath.h>
class IShader;
class IRenderable;

class TowerPlot : public IRegisteredObject
{
public:
	TowerPlot(IShader* ShaderIn, IRenderable* RenderableIn);
	~TowerPlot();
	virtual void Register(IGraphics* GraphicsIn) override;
	virtual void Unregister(IGraphics* GraphicsIn) override;

	bool IsAvailable() const;
	DirectX::XMFLOAT2 GetPosition() const;
	IRenderable* GetRenderable() const;

	void SetPosition(const DirectX::XMFLOAT2 Location);
	void SetScale(const float x, const float y);
	void PlantTower();

	float DistanceFromCenter;
	float Rotation;
private:
	IShader* Shader;
	IRenderable* Renderable;
	Interactable Interact;
	DirectX::XMFLOAT2 Position;
	bool bAvailable = true;
};

