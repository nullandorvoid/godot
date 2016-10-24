#include "AccessibleBaseButton.h"

AccessibleBaseButton::AccessibleBaseButton(Variant b)
	:AccessibleControl(b, STATE_SYSTEM_FOCUSABLE)
{
	if ((bool)getNode().call("is_disabled")) {
		addState(STATE_SYSTEM_UNAVAILABLE);
	}
}

AccessibleBaseButton::~AccessibleBaseButton()
{
}

LONG AccessibleBaseButton::getRole()
{
	return ROLE_SYSTEM_PUSHBUTTON;
}

bool AccessibleBaseButton::hasDefaultAction()
{
	return true;
}

String AccessibleBaseButton::getDefaultAction()
{
	return "Press";
}

bool AccessibleBaseButton::doDefaultAction()
{
	getNode().call("emit_signal", Variant("pressed"));
	return true;
}

bool AccessibleBaseButton::hasKeyboardShortcut()
{
	return false;
}

String AccessibleBaseButton::getKeyboardShortcut()
{
	return "";
}