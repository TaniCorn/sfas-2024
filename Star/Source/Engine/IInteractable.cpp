#include "IInteractable.h"
void IInteractable::Highlighted()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = HighlightColor[i];
	}
}

void IInteractable::Unhighlighted()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = NormalColor[i];
	}
}

void IInteractable::Pressed()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = PressedColor[i];
	}
}

void IInteractable::Unpressed()
{
	for (int i = 0; i < 4; i++)
	{
		Color[i] = NormalColor[i];
	}
}

void IInteractable::SetHighlightColor(float r, float g, float b, float a)
{
	SetArray(HighlightColor, r, g, b, a);
}

void IInteractable::SetPressedColor(float r, float g, float b, float a)
{
	SetArray(PressedColor, r, g, b, a);
}

void IInteractable::SetNormalColor(float r, float g, float b, float a)
{
	SetArray(NormalColor, r, g, b, a);

}

float* IInteractable::GetColorBind()
{
	return Color;
}

void IInteractable::SetArray(float* arrayColor, float r, float g, float b, float a)
{
	arrayColor[0] = r;
	arrayColor[1] = g;
	arrayColor[2] = b;
	arrayColor[3] = a;
}
