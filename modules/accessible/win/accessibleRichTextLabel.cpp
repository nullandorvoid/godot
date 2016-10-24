#include "accessibleRichTextLabel.h"

AccessibleRichTextLabel::AccessibleRichTextLabel(Variant richTextLabel)
	:AccessibleControl(richTextLabel, 0)
{
}

AccessibleRichTextLabel::~AccessibleRichTextLabel()
{
}

bool AccessibleRichTextLabel::hasValue()
{
	return false;
}

String AccessibleRichTextLabel::getValue()
{
	return "";
}

LONG AccessibleRichTextLabel::getRole()
{
	return ROLE_SYSTEM_STATICTEXT;
}

bool AccessibleRichTextLabel::hasDefaultAction()
{
	return false;
}

String AccessibleRichTextLabel::getDefaultAction()
{
	return "";
}

bool AccessibleRichTextLabel::doDefaultAction()
{
	return false;
}

bool AccessibleRichTextLabel::hasKeyboardShortcut()
{
	return false;
}

String AccessibleRichTextLabel::getKeyboardShortcut()
{
	return "";
}

void AccessibleRichTextLabel::setValue(const String &)
{
}
