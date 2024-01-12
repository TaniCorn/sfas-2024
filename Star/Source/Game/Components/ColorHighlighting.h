#pragma once
class ColorHighlighting
{
public:
	ColorHighlighting();
	void Highlighted();
	void Unhighlighted();

	void Update(float DeltaTime);
	void SetHighlightColor(float r, float g, float b, float a);
	void SetNormalColor(float r, float g, float b, float a);
	float* GetColorBind();

private:
	void SetArray(float* arrayColor, float r, float g, float b, float a);

	float Color[4] = { 1,1,1,1 };
	float HighlightColor[4] = { 0.7,0.7,0.8,1 };
	float NormalColor[4] = { 1,1,1,1 };

	float Timer = 0.1f;
	bool bHighlighted = false;
};

