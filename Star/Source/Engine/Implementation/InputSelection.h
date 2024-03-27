#pragma once
class IInput;
class Interactable;
#include <functional>
#include <map>

//The input selection class will remain as is with raw pointers, as it never owns any of the objects. It only references them.
//A better system would be to not have the Interactables be referenced at all but have each interactable object have a unique ID and reference those ID's


enum class ButtonDirection {
	Up,
	Down,
	Left,
	Right
};
class InputSelection
{
public:
	InputSelection(Interactable* FirstSelection);
	~InputSelection();
	void Update(IInput* Input);

	void AddButtonLink(Interactable* Button, Interactable* Link, ButtonDirection Direction);
	std::function<void()> PreviousMenuFunction;

private:
	struct NESW
	{
		Interactable* Up;
		Interactable* Down;
		Interactable* Right;
		Interactable* Left;
	};

	std::map<Interactable*, NESW> InteractableLinks;
	Interactable* CurrentInteractable;
	bool bMoveableX = true;
	bool bMoveableY = true;
};

