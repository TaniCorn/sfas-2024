#pragma once

class IText;
class IRenderable;
class IShader;
#include "IRegisteredObject.h"
class TextButton : public IRegisteredObject
{
public:
	TextButton(IRenderable* RenderableIn, IText* TextIn, IShader* ShdaerIn, float screenx, float screeny);

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
	virtual void Register(IGraphics* GraphicsIn);
	virtual void Unregister(IGraphics* GraphicsIn);

	void AddButtonPosition(float x, float y);
	void AddTextPosition(float x, float y);

	void Highlighted();
	void Unhighlighted();
	void SetHighlightColor(float r, float g, float b, float a);
	float* GetColorBind();
private:
	IShader* Shader;
	IRenderable* Renderable;
	IText* Text;
	float screenX, screenY;
	float halfX, halfY;

	float Color[4] = { 1,1,1,1 };
	float HighlightColor[4] = { 1,1,1,1 };
};

