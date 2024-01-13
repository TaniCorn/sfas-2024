#include "SplashScreen.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "../../Engine/Implementation/DirectX11/DirectX11Text.h"
#include <DirectXColors.h>
SplashScreen::SplashScreen(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = SplashScreenLevel;
}

SplashScreen::~SplashScreen()
{
}

bool SplashScreen::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY = Graphics->GetWindowHeight();
	ITexture* SplashTexture = Graphics->CreateTexture(L"Resource/Textures/Splash.png", "SplashTexture");
	IShader* SplashShader = Graphics->CreateShader(L"Resource/Shaders/FadeColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");

	
	Transform2D TransformText;
	TransformText.PositionX = (screenX/2) - 100;
	TransformText.PositionY = (screenY/2) + 300;
	TransformText.ScaleX = 1;
	TransformText.ScaleY = 1;
	TransformText.Rotation = 0;
	
	Text = Graphics->CreateText("Tanapat Somrid", (screenX / 2) - 380, (screenY / 2) + 400, 2, 2, 0);
	SplashRender = Graphics->CreateFloat4Billboard(SplashShader, SplashTexture, FadeParams);
	SplashRender->SetScale(0.8, 0.8f);

	Graphics->AddText(Text);
	Graphics->AddSpriteToRender(SplashShader, SplashRender);
	
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
