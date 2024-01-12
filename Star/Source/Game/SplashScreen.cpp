#include "SplashScreen.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "../../Source/Engine/Implementation/DirectX11/DirectX11Text.h"
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
	ITexture* SplashTexture = Graphics->CreateTexture(L"Resource/Textures/R.png", "SplashTexture");
	ITexture* ButtonTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");

	IShader* SplashShader = Graphics->CreateShader(L"Resource/Shaders/FadeColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	IShader* SplashShader2 = Graphics->CreateShader(L"Resource/Shaders/FadeColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	IShader* SplashShader3 = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");

	SplashRender = Graphics->CreateFloat4Billboard(SplashShader,SplashTexture, FadeParams);
	SplashRender->SetPosition(500, -500);
	
	Transform2D TransformText;
	TransformText.PositionX = 0;
	TransformText.PositionY = 0;
	TransformText.ScaleX = 1;
	TransformText.ScaleY = 1;
	TransformText.Rotation = 0;
	
	Text = new DirectX11Text("My name is Dende", TransformText, DirectX::Colors::White);

	Graphics->AddText(Text);

	SplashRender2 = Graphics->CreateBillboard(SplashShader, ButtonTexture);
	Graphics->AddSpriteToRender(SplashShader, SplashRender);
	/*Graphics->AddSpriteToRender(SplashShader2, SplashRender2);
	Graphics->AddUIToRender(SplashShader, SplashRender2);*/
	Graphics->AddSpriteToRender(SplashShader3, SplashRender2);
	//Graphics->RemoveUIFromRender(SplashShader, SplashRender2); //Tested works
	//Graphics->RemoveSpriteFromRender(SplashShader, SplashRender); //Tested works
	//Graphics->RemoveText(Text);//Tested works
	
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
