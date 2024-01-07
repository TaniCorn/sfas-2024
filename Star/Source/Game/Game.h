
#pragma once

#include "Engine/IApplication.h"
#include "../../SplashScreen.h"
class IGraphics;
class ITexture;
class IShader;
class IRenderable;

enum RingLayer { Outer, Middle, Inner, NumRings };
enum GameState { Setup, Playing, Test, NumModes };
static const unsigned int NumberOfRings = static_cast<int>(NumRings);

class Game : public IApplication
{
public:

	Game(IGraphics* Graphics, IInput* InputIn);
	virtual ~Game();

	virtual bool IsValid();
	virtual bool Load();
	virtual void Update(float DeltaTime);
	virtual void Cleanup();

private:

	void SetupEachRing();
	void UpdateRingSelection();
	void UpdateSelectedRingRotation();
	void UpdateRingTestSelection();
	void TestRingSolution();

	IRenderable* Rings[NumberOfRings];
	IRenderable* Arrow;
	RingLayer SelectedRing;
	GameState State;
	SplashScreen* Splash;

};

