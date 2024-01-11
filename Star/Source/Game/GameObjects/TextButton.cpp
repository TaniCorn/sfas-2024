#include "TextButton.h"
#include "../Source/Engine/IGraphics.h"
#include "../Source/Engine/IRenderable.h"
#include "../Source/Engine/IText.h"

TextButton::TextButton(IRenderable* RenderableIn, IText* TextIn, IShader* ShaderIn, float screenx, float screeny) : screenX(screenx), screenY(screeny), halfX(screenx / 2), halfY(screeny/2)
{
	Renderable = RenderableIn;
	Text = TextIn;
	Shader = ShaderIn;
	//Renderable->SetPosition(-halfX, halfY);
	Text->SetPosition(halfX, halfY);
	//Text origin is topLeft
	//Renderable origin is center
}


void TextButton::SetPosition(float x, float y)
{
	Renderable->SetPosition(x, y);
	Text->SetPosition(halfX + x, halfY - y);
}

void TextButton::SetRotation(float r)
{
	Renderable->SetRotation(r);
	Text->SetRotation(r);
}

void TextButton::SetScale(float sx, float sy)
{
	Renderable->SetScale(sx, sy);
	Text->SetScale(sx, sy);
}

void TextButton::SetButtonPosition(float x, float y)
{
	Renderable->SetPosition(x, y);
}

void TextButton::SetButtonScale(float sx, float sy)
{
	Renderable->SetScale(sx, sy);
}

void TextButton::SetButtonRotation(float r)
{
	Renderable->SetRotation(r);
}

void TextButton::SetTextRelativePosition(float x, float y)
{
	Text->SetPosition(Renderable->GetTransform().PositionX + halfX + x, halfY - Renderable->GetTransform().PositionY - y);
}

void TextButton::SetTextRelativeRotation(float r)
{
	Text->SetRotation(Renderable->GetTransform().Rotation + r);
}

void TextButton::SetTextRelativeScale(float sx, float sy)
{
	Text->SetScale(Renderable->GetTransform().ScaleX * sx, Renderable->GetTransform().ScaleY * sy);
}

void TextButton::SetTextPosition(float x, float y)
{
	Text->SetPosition(halfX + x, halfX - y);
}

void TextButton::SetTextRotation(float r)
{
	Text->SetRotation(r);
}

void TextButton::SetTextScale(float sx, float sy)
{
	Text->SetScale(sx, sy);
}

void TextButton::Register(IGraphics* GraphicsIn)
{
	GraphicsIn->AddText(Text);
	GraphicsIn->AddUIToRender(Shader, Renderable);
}

void TextButton::Unregister(IGraphics* GraphicsIn)
{
	GraphicsIn->RemoveUIFromRender(Shader, Renderable);
	GraphicsIn->RemoveText(Text);
}

void TextButton::AddButtonPosition(float x, float y)
{
	Renderable->SetPosition(Renderable->GetTransform().PositionX + x, Renderable->GetTransform().PositionY + y);
}

void TextButton::AddTextPosition(float x, float y)
{
	Text->SetPosition(Text->GetXPosition() + x, Text->GetYPosition() - y);
}

void TextButton::Highlighted()
{
	//Renderable.
}

void TextButton::Unhighlighted()
{
}

void TextButton::SetHighlightColor(float r, float g, float b, float a)
{
}

float* TextButton::GetColorBind()
{
	return Color;
}
