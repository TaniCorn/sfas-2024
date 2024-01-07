#pragma once

#include <Windows.h>
#include "ITimer.h"
class WindowsTimer : public ITimer
{
public:
	WindowsTimer();
	~WindowsTimer();

	void Update();

	float GetDeltaTime();
	float GetFPS();
private:
	void CalculateFPS();

	//Used for Delta Time(Non-Exclusive)
	float Frequency;
	INT64 LastClock;
	float DeltaTime;

	float FramesPerSecond;
	float Frames;
	float ElapsedTime;
};

