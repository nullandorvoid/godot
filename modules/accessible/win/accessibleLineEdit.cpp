#include "accessibleLineEdit.h"

AccessibleLineEdit::AccessibleLineEdit(Variant c)
	:AccessibleControl(c, STATE_SYSTEM_FOCUSABLE)
{
}

AccessibleLineEdit::~AccessibleLineEdit()
{
}

bool AccessibleLineEdit::hasValue()
{
	return true;
}

String AccessibleLineEdit::getValue()
{
	return (String)getNode().call("get_text");
}

LONG AccessibleLineEdit::getRole()
{
	return ROLE_SYSTEM_TEXT;
}

bool AccessibleLineEdit::hasDefaultAction()
{
	return false;
}

String AccessibleLineEdit::getDefaultAction()
{
	return String();
}

bool AccessibleLineEdit::doDefaultAction()
{
	return false;
}

bool AccessibleLineEdit::hasKeyboardShortcut()
{
	return false;
}

String AccessibleLineEdit::getKeyboardShortcut()
{
	return String();
}

void AccessibleLineEdit::setValue(const String& s)
{
	try { getNode().call("set_text", Variant(s)); }
	catch (...) {}
}
