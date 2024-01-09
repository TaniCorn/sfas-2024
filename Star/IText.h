#pragma once
class IText
{
public:
	virtual ~IText() {};
	virtual const char* GetText();
	virtual void SetText(const char* TextIn);

	virtual void SetPosition(float x, float y) = 0;
	virtual void SetRotation(float r) = 0;
	virtual void SetScale(float sx, float sy) = 0;
	virtual void SetColor(float r, float g, float b, float a) = 0;


	virtual float GetXPosition() = 0;
	virtual float GetYPosition() = 0;
	virtual float GetRotation() = 0;
	virtual float GetXScale() = 0;
	virtual float GetYScale() = 0;
	virtual float GetRed() = 0;
	virtual float GetGreen() = 0;
	virtual float GetBlue() = 0;
	virtual float GetAlpha() = 0;
protected:
	const char* TextString;
};

