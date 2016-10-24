
#ifndef CONTROL_ACCESSIBLE_BASE_BUTTON_H
#define CONTROL_ACCESSIBLE_BASE_BUTTON_H

#include "accessibleControl.h"

class AccessibleBaseButton : public AccessibleControl
{
public:
	AccessibleBaseButton(Variant button);
	virtual ~AccessibleBaseButton();

	// Inherited via AccessibleControl
	virtual LONG getRole() override;
	virtual bool hasDefaultAction() override;
	virtual String getDefaultAction() override;
	virtual bool doDefaultAction() override;
	virtual bool hasKeyboardShortcut() override;
	virtual String getKeyboardShortcut() override;
};

#endif