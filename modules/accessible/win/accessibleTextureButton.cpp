#include "accessibleTextureButton.h"

AccessibleTextureButton::AccessibleTextureButton(Variant button)
	:AccessibleBaseButton(button)
{
}

AccessibleTextureButton::~AccessibleTextureButton()
{
}

bool AccessibleTextureButton::hasValue()
{
	return false;
}

String AccessibleTextureButton::getValue()
{
	return "";
}

void AccessibleTextureButton::setValue(const String &)
{
}
