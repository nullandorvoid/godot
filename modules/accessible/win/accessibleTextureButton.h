
#ifndef CONTROL_ACCESSIBLE_TEXTURE_BUTTON_H
#define CONTROL_ACCESSIBLE_TEXTURE_BUTTON_H

#include "accessibleBaseButton.h"

class AccessibleTextureButton : public AccessibleBaseButton
{
public:
	AccessibleTextureButton(Variant button);
	virtual ~AccessibleTextureButton();

	// Inherited via AccessibleBaseButton
	virtual bool hasValue() override;
	virtual String getValue() override;
	virtual void setValue(const String &) override;
};

#endif