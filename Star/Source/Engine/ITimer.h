#pragma once
class ITimer
{
public:
	virtual ~ITimer() {};
	virtual void Update() = 0;
	virtual float GetDeltaTime() = 0;
	virtual float GetFPS() = 0;
};


