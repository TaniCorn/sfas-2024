#include "WindowsTimer.h"
WindowsTimer::WindowsTimer()
{
	INT64 ClockFrequency;
	QueryPerformanceFrequency((LARGE_INTEGER*)&ClockFrequency);
	if (ClockFrequency == 0)
	{
		MessageBox(NULL, "No support for high performance timer", "ERROR", MB_OK);
	}

	Frequency = (float)(ClockFrequency);

	ElapsedTime = 0.f;
	Frames = 0.f;
	FramesPerSecond = 0.f;
}
WindowsTimer::~WindowsTimer()
{
}

void WindowsTimer::Update()
{
	//Calculate DeltaTime
	INT64 CurrentClock;
	float TimeDifference;
	QueryPerformanceCounter((LARGE_INTEGER*)&CurrentClock);
	TimeDifference = (float)(CurrentClock - LastClock);
	DeltaTime = TimeDifference / Frequency;

	// Restart the timer.
	LastClock = CurrentClock;
}

float WindowsTimer::GetDeltaTime()
{
	return DeltaTime;
}

float WindowsTimer::GetFPS()
{
	// We only calculate FPS when we request it
	CalculateFPS();

	return FramesPerSecond;
}

void WindowsTimer::CalculateFPS()
{
	Frames += 1.f;
	ElapsedTime += DeltaTime;
	if (ElapsedTime > 1.0f)
	{
		FramesPerSecond = Frames / ElapsedTime;
		Frames = 0.0f;
		ElapsedTime = 0.0f;
	}
}
