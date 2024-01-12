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

	float Color[4] = { 1,1,1,1 };
	float HighlightColor[4] = { 0.7,0.7,0.8,1 };
	float PressedColor[4]{ 0.5,0.5,0.6, 1 };
	float NormalColor[4] = { 1,1,1,1 };
};

