#include "ColorHighlighting.h"

ColorHighlighting::ColorHighlighting()
{
}

void ColorHighlighting::Highlighted()
{
	bHighlighted = true;
	for (int i = 0; i < 4; i++)
	{
		Color[i] = HighlightColor[i];
	}
}

void ColorHighlighting::Unhighlighted()
{
	bHighlighted = false;
	for (int i = 0; i < 4; i++)
	{
		Color[i] = NormalColor[i];
	}
}

void ColorHighlighting::Update(float DeltaTime)
{
	if (bHighlighted)
	{
		Timer -= DeltaTime;
		if (Timer < 0)
		{
			Unhighlighted();
			Timer = 0.1f;
		}
	}
}

void ColorHighlighting::SetHighlightColor(float r, float g, float b, float a)
{
	SetArray(HighlightColor, r, g, b, a);
}

void ColorHighlighting::SetNormalColor(float r, float g, float b, float a)
{
	SetArray(NormalColor, r, g, b, a);

}

float* ColorHighlighting::GetColorBind()
{
	return Color;
}

void ColorHighlighting::SetArray(float* arrayColor, float r, float g, float b, float a)
{
	arrayColor[0] = r;
	arrayColor[1] = g;
	arrayColor[2] = b;
	arrayColor[3] = a;
}
