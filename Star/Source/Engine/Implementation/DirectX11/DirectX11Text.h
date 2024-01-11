#pragma once

#include "Engine/Transform2D.h"
#include "../../IText.h"
#include <DirectXMath.h>
class DirectX11Text : public IText
{
public:
	DirectX11Text(const char* TextIn, Transform2D TranformIn, DirectX::XMVECTOR ColorIn);
	DirectX11Text(const char* TextIn, DirectX::XMFLOAT2 Position, DirectX::XMFLOAT2 Scale, float rotation, DirectX::XMVECTOR ColorIn);
	virtual ~DirectX11Text();
	const Transform2D& GetTransform() const;
	virtual void SetPosition(float x, float y);
	virtual void SetRotation(float r);
	virtual void SetScale(float sx, float sy);
	virtual void SetColor(float r, float g, float b, float a);


	virtual float GetXPosition();
	virtual float GetYPosition();
	virtual float GetRotation();
	virtual float GetXScale();
	virtual float GetYScale();
	virtual float GetRed();
	virtual float GetGreen();
	virtual float GetBlue();
	virtual float GetAlpha();
protected:
	Transform2D Transform;
	DirectX::XMVECTOR Color;
};

