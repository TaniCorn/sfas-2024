
#pragma once

#include "Engine/IApplication.h"
class IGraphics;
class ITexture;
class IShader;
class IRenderable;
enum class Level;
class ILevel;

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

	Level CurrentLevelIdentifier;
	ILevel* CurrentLevel;
	ILevel* LoadingScreenLevel; //If implementing Asyncronous loading screens

	bool bQuitGame = false;

};

