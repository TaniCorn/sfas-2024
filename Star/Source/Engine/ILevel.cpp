#include "ILevel.h"

ILevel::ILevel(IGraphics* GraphicsIn, IInput* InputIn) : Graphics(GraphicsIn), Input(InputIn)
{
}

ILevel::~ILevel()
{
}

Level ILevel::LevelSwitch()
{
    return LevelSwitchKey;
}
