#include "RingSelection.h"
#include "../../Engine/IInput.h"
#include "DefenceRing.h"
void RingSelection::Update(float DeltaTime, IInput* Input)
{
	if (Input->IsPressed(InputAction::ShoulderButtonLeft))
	{
		// Change ring selection towards outer
		ChangeRing(true);
	}
	else if (Input->IsPressed(InputAction::ShoulderButtonRight))
	{
		// Change ring selection towards inner
		ChangeRing(false);
	}

	if (Input->IsHeld(InputAction::TriggerLeft))
	{
		CurrentRing->Rotate(1, DeltaTime);
	}
	else if (Input->IsHeld(InputAction::TriggerRight))
	{
		CurrentRing->Rotate(-1, DeltaTime);
	}
}

RingSelection::RingSelection(DefenceRing* InnerRing) : RingLinks()
{
	CurrentRing = InnerRing;
	RingLinks[InnerRing] = std::pair<DefenceRing*, DefenceRing*>();
}

void RingSelection::AddLink(DefenceRing* Ring, DefenceRing* Link, bool bIsOuter)
{
	if (bIsOuter)
	{
		RingLinks[Ring].first = Link;
	}
	else 
	{
		RingLinks[Ring].second = Link;
	}
}

void RingSelection::ChangeRing(bool bToOuter)
{
	if (bToOuter)
	{
		if (RingLinks[CurrentRing].first != nullptr)
		{
			CurrentRing->Interact.Unhighlighted();
			CurrentRing = RingLinks[CurrentRing].first;
			CurrentRing->Interact.Highlighted();
		}
	}
	else 
	{
		if (RingLinks[CurrentRing].second != nullptr)
		{
			CurrentRing->Interact.Unhighlighted();
			CurrentRing = RingLinks[CurrentRing].second;
			CurrentRing->Interact.Highlighted();

		}
	}

}
