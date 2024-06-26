#pragma once
class DefenceRing;
class IInput;
#include <map>

//This couldn't use the InputSelection class as this requires seperate inputs, RB LB not thumbstick control

class RingSelection
{
public:
	RingSelection();
	void Update(float DeltaTime, IInput* Input);
	void AddLink(DefenceRing* Ring, DefenceRing* Link, bool bIsOuter);
	void SetFirstRing(DefenceRing* InnerRing);
private:
	void ChangeRing(bool bToOuter);
	std::map<DefenceRing*, std::pair<DefenceRing*, DefenceRing*>> RingLinks;
	DefenceRing* CurrentRing;
};

