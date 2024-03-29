#pragma once
class DefenceRing;
class IInput;
#include <map>

class RingSelection
{
public:
	RingSelection(DefenceRing* InnerRing);
	void Update(float DeltaTime, IInput* Input);
	void AddLink(DefenceRing* Ring, DefenceRing* Link, bool bIsOuter);
private:
	void ChangeRing(bool bToOuter);
	std::map<DefenceRing*, std::pair<DefenceRing*, DefenceRing*>> RingLinks;
	DefenceRing* CurrentRing;
};

