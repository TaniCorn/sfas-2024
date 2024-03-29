#pragma once

class IText;
class IRenderable;
class IShader;
#include "../../Engine/IRegisteredObject.h"
#include "../Components/Interactable.h"

class TextButton : public IRegisteredObject
{
public:
	TextButton(IRenderable* RenderableIn, IText* TextIn, IShader* ShaderIn, float screenx, float screeny);

	virtual void Register(IGraphics* GraphicsIn) override;
	virtual void Unregister(IGraphics* GraphicsIn) override;

	void AddButtonPosition(float x, float y);
	void AddTextPosition(float x, float y);
	void SetPosition(float x, float y);
	void SetRotation(float r);
	void SetScale(float sx, float sy);
	void SetButtonPosition(float x, float y);
	void SetButtonScale(float sx, float sy);
	void SetButtonRotation(float r);
	void SetTextRelativePosition(float x, float y);
	void SetTextRelativeRotation(float r);
	void SetTextRelativeScale(float sx, float sy);
	void SetTextPosition(float x, float y);
	void SetTextRotation(float r);
	void SetTextScale(float sx, float sy);

	Interactable Interact;
private:

	IShader* Shader;
	IRenderable* Renderable;
	IText* Text;
	float halfX, halfY;
};

