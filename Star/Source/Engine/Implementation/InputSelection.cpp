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
	XMovement(Input);
	YMovement(Input);
	//Confirm Selection
	if (Input->IsPressed(InputAction::ButtonBottom))
	{
		if (CurrentInteractable->BoundFunction)
		{
			CurrentInteractable->BoundFunction();
		}
	}
	//Back button
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
	case ButtonDirection::Up:
		InteractableLinks[Button].Up = Link;
		break;
	case ButtonDirection::Down:
		InteractableLinks[Button].Down = Link;
		break;
	case ButtonDirection::Left:
		InteractableLinks[Button].Left = Link;
		break;
	case ButtonDirection::Right:
		InteractableLinks[Button].Right = Link;
		break;
	default:
		return;
	}
}

void InputSelection::XMovement(IInput* Input)
{
	float xVal = Input->GetValue(InputAction::LeftStickXAxis);

	//Moves to new UI, unhighlights old one and highlights new one
	if (bMoveableX)
	{
		bool Left = xVal < 0;
		bool Right = xVal > 0;
		if (Left)
		{
			if (InteractableLinks[CurrentInteractable].Left != nullptr)
			{
				CurrentInteractable->Unhighlighted();
				CurrentInteractable = InteractableLinks[CurrentInteractable].Left;
				CurrentInteractable->Highlighted();
				bMoveableX = false;
			}
		}
		else if (Right)
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
	else 
	{
		//Prevents moving until the stick is back near the center
		if (xVal <= 0.1 && xVal >= -0.1)
		{
			bMoveableX = true;
		}
	}
}

void InputSelection::YMovement(IInput* Input)
{
	float yVal = Input->GetValue(InputAction::LeftStickYAxis);

	//Moves to new UI, unhighlights old one and highlights new one
	if (bMoveableY)
	{
		bool Left = yVal < 0;
		bool Right = yVal > 0;
		if (Left)
		{
			if (InteractableLinks[CurrentInteractable].Down != nullptr)
			{
				CurrentInteractable->Unhighlighted();
				CurrentInteractable = InteractableLinks[CurrentInteractable].Down;
				CurrentInteractable->Highlighted();
				bMoveableY = false;
			}

		}
		else if (Right)
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
		//Prevents moving until the stick is back near the center
		if (yVal <= 0.1 && yVal >= -0.1)
		{
			bMoveableY = true;
		}
	}
}
