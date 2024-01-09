#include "DirectX11Text.h"

DirectX11Text::DirectX11Text(const char* TextIn, Transform2D TranformIn, DirectX::XMVECTOR ColorIn) : Color(ColorIn)
{
	TextString = TextIn;
	Transform.PositionX = TranformIn.PositionX;
	Transform.PositionY = TranformIn.PositionY;
	Transform.ScaleX = TranformIn.ScaleX;
	Transform.ScaleY = TranformIn.ScaleY;
	Transform.Rotation = TranformIn.Rotation;
}

DirectX11Text::DirectX11Text(const char* TextIn, DirectX::XMFLOAT2 Position, DirectX::XMFLOAT2 Scale, float Rotation, DirectX::XMVECTOR ColorIn) : Color(ColorIn)
{
	TextString = TextIn;
	Transform.PositionX = Position.x;
	Transform.PositionY = Position.y;
	Transform.ScaleX = Scale.x;
	Transform.ScaleY = Scale.y;
	Transform.Rotation = Rotation;
}

DirectX11Text::~DirectX11Text()
{
}

const Transform2D& DirectX11Text::GetTransform() const
{
	return Transform;
}

void DirectX11Text::SetPosition(float x, float y)
{
	Transform.PositionX = x;
	Transform.PositionY = y;
}

void DirectX11Text::SetRotation(float r)
{
	Transform.Rotation = r;
}

void DirectX11Text::SetScale(float sx, float sy)
{
	Transform.ScaleX = sx;
	Transform.ScaleY = sy;
}

void DirectX11Text::SetColor(float r, float g, float b, float a)
{
	Color = DirectX::XMVectorSet(r, g, b, a);
}

float DirectX11Text::GetXPosition()
{
	return Transform.PositionX;
}

float DirectX11Text::GetYPosition()
{
	return Transform.PositionY;
}

float DirectX11Text::GetRotation()
{
	return Transform.Rotation;
}

float DirectX11Text::GetXScale()
{
	return Transform.ScaleX;
}

float DirectX11Text::GetYScale()
{
	return Transform.ScaleY;
}

float DirectX11Text::GetRed()
{
	return DirectX::XMVectorGetX(Color);
}

float DirectX11Text::GetGreen()
{
	return DirectX::XMVectorGetY(Color);
}

float DirectX11Text::GetBlue()
{
	return DirectX::XMVectorGetZ(Color);
}

float DirectX11Text::GetAlpha()
{
	return  DirectX::XMVectorGetW(Color);
}
