#include "IText.h"
const char* IText::GetText()
{
	return TextString;
}

void IText::SetText(const char* TextIn)
{
	TextString = TextIn;
}
