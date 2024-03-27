#pragma once
#include <functional>

class Interactable
{
public:
	Interactable();
	void Highlighted();
	void Unhighlighted();
	void Pressed();
	void Unpressed();
	void SetHighlightColor(float r, float g, float b, float a);
	void SetPressedColor(float r, float g, float b, float a);
	void SetNormalColor(float r, float g, float b, float a);
	float* GetColorBind();

	std::function<void()> BoundFunction;
protected:
	void SetArray(float* arrayColor, float r, float g, float b, float a);

	float Color[4] = { 1.0f,1.0f,1.0f,1.0f };
	float HighlightColor[4] = { 0.7f,0.7f,0.8f,1.0f };
	float PressedColor[4]{ 0.5f,0.5f,0.6f, 1.0f };
	float NormalColor[4] = { 1.0f,1.0f,1.0f,1.0f };
};

