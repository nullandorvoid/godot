#include "accessibleButton.h"

AccessibleButton::AccessibleButton(Variant button)
	:AccessibleBaseButton(button)
{
}

AccessibleButton::~AccessibleButton()
{
}

String AccessibleButton::getName()
{
	return (String)getNode().call("get_text");
}

bool AccessibleButton::hasValue()
{
	return false;
}

String AccessibleButton::getValue()
{
	return "";
}

void AccessibleButton::setValue(const String & value)
{
}
