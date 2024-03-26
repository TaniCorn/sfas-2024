
#pragma once

#include "Engine/IApplication.h"
class IGraphics;
class ITexture;
class IShader;
class IRenderable;
enum Level;
class ILevel;

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

	void SwitchLevel(Level NextLevelIdentfier);

	IRenderable* Rings[NumberOfRings];
	IRenderable* Arrow;
	RingLayer SelectedRing;
	GameState State;

	Level CurrentLevelIdentifier;
	ILevel* CurrentLevel;
	ILevel* LoadingScreenLevel; //If implementing Asyncronous loading screens

	bool bQuitGame = false;

};

