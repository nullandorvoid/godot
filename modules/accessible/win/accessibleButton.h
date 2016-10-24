
#ifndef CONTROL_ACCESSIBLE_BUTTON_H
#define CONTROL_ACCESSIBLE_BUTTON_H

#include "accessibleBaseButton.h"

class AccessibleButton : public AccessibleBaseButton
{
public:
	AccessibleButton(Variant button);
	virtual ~AccessibleButton();

	virtual String getName() override;

	virtual bool hasValue() override;
	virtual String getValue() override;
	virtual void setValue(const String &) override;
};

#endif