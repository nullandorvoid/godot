#include "accessibleRange.h"
#include <sstream>


AccessibleRange::AccessibleRange(Variant control)
	:AccessibleControl(control, STATE_SYSTEM_FOCUSABLE)
{
}


AccessibleRange::~AccessibleRange()
{
}

bool AccessibleRange::hasValue()
{
	return true;
}

String AccessibleRange::getValue()
{
	return rtos((float)getNode().call("get_value"));
}

LONG AccessibleRange::getRole()
{
	return ROLE_SYSTEM_SLIDER;
}

bool AccessibleRange::hasDefaultAction()
{
	return false;
}

String AccessibleRange::getDefaultAction()
{
	return String();
}

bool AccessibleRange::doDefaultAction()
{
	return false;
}

bool AccessibleRange::hasKeyboardShortcut()
{
	return false;
}

String AccessibleRange::getKeyboardShortcut()
{
	return String();
}

void AccessibleRange::setValue(const String & s)
{
	try {
		float newValue = s.to_float();
		getNode().call("set_value", Variant(newValue));
	}
	catch(...){}
}
