#include "accessibleLabel.h"


AccessibleLabel::AccessibleLabel(Variant label)
	:AccessibleControl(label, 0)
{
}


AccessibleLabel::~AccessibleLabel()
{
}

String AccessibleLabel::getName()
{
	return (String)getNode().call("get_text");
}

bool AccessibleLabel::hasValue()
{
	return false;
}

String AccessibleLabel::getValue()
{
	return "";
}

LONG AccessibleLabel::getRole()
{
	return ROLE_SYSTEM_STATICTEXT;
}

bool AccessibleLabel::hasDefaultAction()
{
	return false;
}

String AccessibleLabel::getDefaultAction()
{
	return "";
}

bool AccessibleLabel::doDefaultAction()
{
	return false;
}

bool AccessibleLabel::hasKeyboardShortcut()
{
	return false;
}

String AccessibleLabel::getKeyboardShortcut()
{
	return "";
}

void AccessibleLabel::setValue(const String &)
{
}
