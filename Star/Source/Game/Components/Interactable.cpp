#include "Interactable.h"
Interactable::Interactable()
{
}
void Interactable::Highlighted()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = HighlightColor[i];
	}
}

void Interactable::Unhighlighted()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = NormalColor[i];
	}
}

void Interactable::Pressed()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = PressedColor[i];
	}
}

void Interactable::Unpressed()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = NormalColor[i];
	}
}

void Interactable::SetHighlightColor(float r, float g, float b, float a)
{
	SetArray(HighlightColor, r, g, b, a);
}

void Interactable::SetPressedColor(float r, float g, float b, float a)
{
	SetArray(PressedColor, r, g, b, a);
}

void Interactable::SetNormalColor(float r, float g, float b, float a)
{
	SetArray(NormalColor, r, g, b, a);

}

float* Interactable::GetColorBind()
{
	return Color;
}

void Interactable::SetArray(float* arrayColor, float r, float g, float b, float a)
{
	arrayColor[0] = r;
	arrayColor[1] = g;
	arrayColor[2] = b;
	arrayColor[3] = a;
}
