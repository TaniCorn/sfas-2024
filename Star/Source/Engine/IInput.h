
#pragma once

enum InputAction
{
	ButtonLeft,
	ButtonRight,
	ButtonTop,
	ButtonBottom,

	DirectionPadLeft,
	DirectionPadRight,
	DirectionPadTop,
	DirectionPadBottom,

	LeftStickXAxis,
	LeftStickYAxis,
	LeftStickPress,

	RightStickXAxis,
	RightStickYAxis,
	RightStickPress,

	TriggerLeft,
	TriggerRight,
	ShoulderButtonLeft,
	ShoulderButtonRight,

	SpecialLeft,
	SpecialRight,

	NumActions,

	DefaultSelect = ButtonBottom,
	DefaultBack = ButtonRight,

};

class IInput
{
public:

	IInput();

	virtual void Update();

	virtual float GetValue(InputAction action) const;
	virtual bool IsPressed(InputAction action, float threshold = 0.5f) const;
	virtual bool IsReleased(InputAction action, float threshold = 0.5f) const;
	virtual bool IsHeld(InputAction action, float threshold = 0.5f) const;

	static const unsigned int NumInputActions = static_cast<unsigned int>(NumActions);

protected:
	
	float CurrentState[NumInputActions];
	float PreviousState[NumInputActions];

};

