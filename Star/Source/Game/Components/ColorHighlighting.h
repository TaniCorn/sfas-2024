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

	float Color[4] = { 1.0f,1.0f,1.0f,1.0f };
	float HighlightColor[4] = { 0.7f,0.7f,0.8f,1.0f };
	float NormalColor[4] = { 1.0f,1.0f,1.0f,1.0f };

	float Timer = 0.1f;
	bool bHighlighted = false;
};

