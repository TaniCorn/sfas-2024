#include "ILevel.h"

ILevel::ILevel(IGraphics* GraphicsIn, IInput* InputIn) : Graphics(GraphicsIn), Input(InputIn)
{
}

ILevel::~ILevel()
{
}

LevelId ILevel::LevelSwitch()
{
    return LevelSwitchKey;
}
