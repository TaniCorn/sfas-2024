#pragma once
class IInput;
class Interactable;
#include <functional>
#include <map>
enum ButtonDirection {
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

