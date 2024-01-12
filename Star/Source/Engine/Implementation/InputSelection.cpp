#include "InputSelection.h"
#include "../../Game/Components/Interactable.h"
#include "../IInput.h"

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
	if (bMoveableX)
	{
		if (xVal < 0)
		{
			if (InteractableLinks[CurrentInteractable].Left != nullptr)
			{
				CurrentInteractable->Unhighlighted();
				CurrentInteractable = InteractableLinks[CurrentInteractable].Left;
				CurrentInteractable->Highlighted();
				bMoveableX = false;
			}
		}
		else if (xVal > 0)
		{
			if (InteractableLinks[CurrentInteractable].Right != nullptr)
			{
				CurrentInteractable->Unhighlighted();
				CurrentInteractable = InteractableLinks[CurrentInteractable].Right;
				CurrentInteractable->Highlighted();
				bMoveableX = false;
			}
		}
	}
	else {
		if (xVal <= 0.1 && xVal >= -0.1)
		{
			bMoveableX = true;
		}
	}

	if (bMoveableY)
	{
		if (yVal < 0)
		{
			if (InteractableLinks[CurrentInteractable].Down != nullptr)
			{
				CurrentInteractable->Unhighlighted();
				CurrentInteractable = InteractableLinks[CurrentInteractable].Down;
				CurrentInteractable->Highlighted();
				bMoveableY = false;
			}

		}
		else if (yVal > 0)
		{
			if (InteractableLinks[CurrentInteractable].Up != nullptr)
			{
				CurrentInteractable->Unhighlighted();
				CurrentInteractable = InteractableLinks[CurrentInteractable].Up;
				CurrentInteractable->Highlighted();
				bMoveableY = false;
			}
		}
	}
	else 
	{
		if (yVal <= 0.1 && yVal >= -0.1)
		{
			bMoveableY = true;
		}
	}


	if (Input->IsPressed(InputAction::ButtonBottom))
	{
		if (CurrentInteractable->BoundFunction)
		{
			CurrentInteractable->BoundFunction();
		}
	}
	if (Input->IsPressed(InputAction::ButtonRight))
	{
		if (PreviousMenuFunction)
		{
			PreviousMenuFunction();
		}
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
