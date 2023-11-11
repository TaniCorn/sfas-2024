
#pragma once

class IGraphics;
class IInput;

class IApplication
{
public:

	IApplication(IGraphics* GraphicsIn, IInput* InputIn);
	virtual ~IApplication();

	virtual bool IsValid() = 0;
	virtual bool Load() = 0;
	virtual void Update() = 0;
	virtual void Cleanup() = 0;

protected:

	IGraphics* Graphics;
	IInput* Input;

};

