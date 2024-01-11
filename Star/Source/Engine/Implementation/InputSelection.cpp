#include "InputSelection.h"
#include "../IInput.h"
#include "../Interactable.h"

InputSelection::InputSelection(Interactable* FirstSelection) : InteractableLinks()
{
	InteractableLinks[FirstSelection] = NESW();
	CurrentInteractable = FirstSelection;
	CurrentInteractable->Highlighted();
}

InputSelection::~InputSelection()
{
	InteractableLinks.clear();
	CurrentInteractable = nullptr;
}

void InputSelection::Update(IInput* Input)
{
	float xVal = Input->GetValue(InputAction::LeftStickXAxis);
	float yVal = Input->GetValue(InputAction::LeftStickYAxis);
	if (xVal < 0)
	{
		if (InteractableLinks[CurrentInteractable].Left != nullptr) 
		{
			CurrentInteractable->Unhighlighted();
			CurrentInteractable = InteractableLinks[CurrentInteractable].Left;
			CurrentInteractable->Highlighted();
		}
	}
	else if (xVal > 0)
	{
		if (InteractableLinks[CurrentInteractable].Right != nullptr)
		{
			CurrentInteractable->Unhighlighted();
			CurrentInteractable = InteractableLinks[CurrentInteractable].Right;
			CurrentInteractable->Highlighted();
		}
	}
	else if (yVal < 0)
	{
		if (InteractableLinks[CurrentInteractable].Down != nullptr)
		{
			CurrentInteractable->Unhighlighted();
			CurrentInteractable = InteractableLinks[CurrentInteractable].Down;
			CurrentInteractable->Highlighted();
		}

	}
	else if (yVal > 0)
	{
		if (InteractableLinks[CurrentInteractable].Up != nullptr)
		{
			CurrentInteractable->Unhighlighted();
			CurrentInteractable = InteractableLinks[CurrentInteractable].Up;
			CurrentInteractable->Highlighted();
		}
	}
	if (Input->IsPressed(InputAction::ButtonBottom))
	{
		CurrentInteractable->BoundFunction();
	}
}

void InputSelection::AddButtonLink(Interactable* Button, Interactable* Link, ButtonDirection Direction)
{
	switch (Direction)
	{
	case Up:
		InteractableLinks[Button].Up = Link;
		break;
	case Down:
		InteractableLinks[Button].Down = Link;
		break;
	case Left:
		InteractableLinks[Button].Left = Link;
		break;
	case Right:
		InteractableLinks[Button].Right = Link;
		break;
	default:
		return;
	}
}
