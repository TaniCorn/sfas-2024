#include "SplashScreen.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "DirectX11Text.h"
#include <DirectXColors.h>
SplashScreen::SplashScreen(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = SplashScreenLevel;
}

SplashScreen::~SplashScreen()
{

}

Level SplashScreen::LevelSwitch()
{
	return LevelSwitchKey;
}

bool SplashScreen::Load()
{
	ITexture* SplashTexture = Graphics->CreateTexture(L"Resource/Textures/R.png", "SplashTexture");

	IShader* SplashShader = Graphics->CreateShader(L"Resource/Shaders/FadeColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", SplashTexture);

	SplashRender = Graphics->CreateFade(SplashShader, FadeParams);

	Transform2D TransformText;
	TransformText.PositionX = 0;
	TransformText.PositionY = 0;
	TransformText.ScaleX = 1;
	TransformText.ScaleY = 1;
	TransformText.Rotation = 0;
	Text = new DirectX11Text("My name is Dende", TransformText, DirectX::Colors::White);

	Graphics->AddText(Text);
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
		LevelSwitchKey = MainMenuLevel;
	}
}

void SplashScreen::Cleanup()
{
	Graphics->Cleanup();
}
