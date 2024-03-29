#pragma once
#include "../../Engine/ILevel.h"

class IRenderable;
class IText;

class SplashScreen : public ILevel
{
public:
	SplashScreen(IGraphics* Graphics, IInput* InputIn);
	virtual ~SplashScreen();

	virtual bool Load() override;
	virtual void Update(float DeltaTime) override;
	virtual void Cleanup() override;

private:
	const float SplashTime = 4.0f;
	const float InTransitionTime = 0.5f;
	const float OutTransitionTime = 1.0f;
	float Time = 0;
	bool bReverse = false;
	bool bCompleted = false;

	float FadeParams[4] = { 1,1,1,0 };

	IRenderable* SplashRender;
	IText* Text;
};

