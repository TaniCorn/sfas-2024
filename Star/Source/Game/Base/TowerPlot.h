#pragma once
#include "../Components/Interactable.h"
#include "../../Engine/IRegisteredObject.h"
#include <DirectXMath.h>
class IShader;
class IRenderable;
class Tower;

class TowerPlot : public IRegisteredObject
{
public:
	TowerPlot(IShader* ShaderIn, IRenderable* RenderableIn);
	~TowerPlot();
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);
	void SetPosition(DirectX::XMFLOAT2 Location);
	DirectX::XMFLOAT2 GetPosition() const;
	void SetScale(float x, float y);
	bool IsAvailable();
	void PlantTower(Tower* TowerToPlant);
	IRenderable* GetRenderable();
	IRenderable* GetTowerRenderable();
	Interactable Interact;
	Tower* PlantedTower;
	float DistanceFromCenter;
	float Rotation;
private:
	IShader* Shader;
	IRenderable* Renderable;
	DirectX::XMFLOAT2 Position;
};

