#pragma once

#include <math.h>
#include <DirectXMath.h>

namespace DXHelper 
{
	static float Magnitude(float x1, float y1) {
		return (x1 * x1) + (y1 * y1);
	}
	static float MagnitudeSqrRoot(float x1, float y1) {
		return sqrtf(Magnitude(x1, y1));
	}
	static float Magnitude(const DirectX::XMFLOAT2 v1)
	{
		return (v1.x * v1.x) + (v1.y * v1.y);
	}
	static float MagnitudeSqrRoot(const DirectX::XMFLOAT2 v1)
	{
		return sqrtf(Magnitude(v1));
	}
	static DirectX::XMFLOAT2 Normalise(const DirectX::XMFLOAT2 v1) {
		float length = MagnitudeSqrRoot(v1);
		DirectX::XMFLOAT2 normalisedVector;
		normalisedVector.x = (v1.x / length);
		normalisedVector.y = (v1.y / length);
		return normalisedVector;
	}
	static float DotProduct(const DirectX::XMFLOAT2 v1, const DirectX::XMFLOAT2 v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	//Unless I'm just an absolute moron, I can't see XMFLOAT2 having an additive or subtractive overload, and I don't really want to fiddle with the original files
	static DirectX::XMFLOAT2 Subtract(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x - b.x, a.y - b.y);
	}
	static DirectX::XMFLOAT2 Add(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x + b.x, a.y + b.y);
	}
	static DirectX::XMFLOAT2 Multiply(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x * b.x, a.y * b.y);
	}
	static DirectX::XMFLOAT2 Multiply(DirectX::XMFLOAT2 a, float b)
	{
		return DirectX::XMFLOAT2(a.x * b, a.y * b);
	}
}
