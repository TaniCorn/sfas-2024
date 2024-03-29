#include "ILevel.h"

ILevel::ILevel(IGraphics* GraphicsIn, IInput* InputIn) : Graphics(GraphicsIn), Input(InputIn), LevelSwitchKey(LevelId::SplashScreenLevel)
{
}

ILevel::~ILevel()
{
}

LevelId ILevel::LevelSwitch()
{
    return LevelSwitchKey;
}
