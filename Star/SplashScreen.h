#pragma once
#include "ILevel.h"

class IRenderable;
class IText;

class SplashScreen : public ILevel
{
public:
	SplashScreen(IGraphics* Graphics, IInput* InputIn);
	virtual ~SplashScreen();

	virtual bool Load();
	virtual void Update(float DeltaTime);
	virtual void Cleanup();

private:
	const float SplashTime = 4.0f;
	const float InTransitionTime = 0.5f;
	const float OutTransitionTime = 1.0f;
	float Time = 0;
	bool bReverse = false;
	bool bCompleted = false;

	float FadeParams[4] = { 1,1,1,0 };

	IRenderable* SplashRender;
	IRenderable* SplashRender2;
	IText* Text;
};

