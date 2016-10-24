#include "accessibleOptionButton.h"

AccessibleOptionButton::AccessibleOptionButton(Variant control)
	:AccessibleButton(control)
{
}

AccessibleOptionButton::~AccessibleOptionButton()
{
}

bool AccessibleOptionButton::hasValue()
{
	return true;
}

String AccessibleOptionButton::getValue()
{
	return (String)getNode().call("get_text");
}

LONG AccessibleOptionButton::getRole()
{
	return ROLE_SYSTEM_BUTTONDROPDOWN;
}

void AccessibleOptionButton::setValue(const String& s)
{
	getNode().call("set_text", Variant(s));
}
