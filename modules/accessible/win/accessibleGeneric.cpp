#include "accessibleGeneric.h"



AccessibleGeneric::AccessibleGeneric(Variant control, LONG defaultState, LONG role)
	:AccessibleControl(control, defaultState)
{
	this->role = role;
}

AccessibleGeneric::~AccessibleGeneric()
{
}

bool AccessibleGeneric::hasValue()
{
	return false;
}

String AccessibleGeneric::getValue()
{
	return String();
}

LONG AccessibleGeneric::getRole()
{
	return role;
}

bool AccessibleGeneric::hasDefaultAction()
{
	return false;
}

String AccessibleGeneric::getDefaultAction()
{
	return String();
}

bool AccessibleGeneric::doDefaultAction()
{
	return false;
}

bool AccessibleGeneric::hasKeyboardShortcut()
{
	return false;
}

String AccessibleGeneric::getKeyboardShortcut()
{
	return String();
}

void AccessibleGeneric::setValue(const String &)
{
}
