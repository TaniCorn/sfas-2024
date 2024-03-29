
#pragma once

#include "Engine/IApplication.h"
class IGraphics;
class ITexture;
class IShader;
class IRenderable;
enum class LevelId;
class ILevel;

class Game : public IApplication
{
public:

	Game(IGraphics* Graphics, IInput* InputIn);
	virtual ~Game();

	virtual bool IsValid() override;
	virtual bool Load() override;
	virtual void Update(float DeltaTime) override;
	virtual void Cleanup() override;

private:

	void SwitchLevel(LevelId NextLevelIdentfier);

	LevelId CurrentLevelIdentifier;
	ILevel* CurrentLevel;
	ILevel* LoadingScreenLevel; //If implementing Asyncronous loading screens

	bool bQuitGame = false;

};

