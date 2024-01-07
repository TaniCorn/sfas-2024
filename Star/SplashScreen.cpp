#include "SplashScreen.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

SplashScreen::SplashScreen(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
}

SplashScreen::~SplashScreen()
{
	if (SplashRender)
	{
		delete SplashRender;
		SplashRender = nullptr;
	}
}

bool SplashScreen::IsValid()
{
	return true;
}

bool SplashScreen::Load()
{
	ITexture* SplashTexture = Graphics->CreateTexture(L"Resource/Textures/R.png", "SplashTexture");
	IShader* SplashShader = Graphics->CreateShader(L"Resource/Shaders/FadeColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", SplashTexture);

	SplashRender = Graphics->CreateFade(SplashShader, FadeParams);

	return true;
}

void SplashScreen::Update(float DeltaTime)
{

	//Fade effects
	if (Time < InTransitionTime && !bReverse)
	{
		Time += DeltaTime;
		FadeParams[3] = Time;
	}
	else if (!bReverse)
	{
		Time += DeltaTime;
		FadeParams[3] = 1;

		if (Time > (SplashTime - OutTransitionTime))
		{
			Time = OutTransitionTime;
			bReverse = true;
		}
	}
	if (bReverse && Time > 0)
	{
		Time -= DeltaTime;
		FadeParams[3] = Time/OutTransitionTime;
		bCompleted = true;
	}
}

void SplashScreen::Cleanup()
{
}
