#ifndef GENERIC_ACCESSIBLE_H
#define GENERIC_ACCESSIBLE_H

#include "accessibleControl.h"
class AccessibleGeneric :public AccessibleControl
{
public:
	AccessibleGeneric(Variant control, LONG defaultState, LONG role);
	virtual ~AccessibleGeneric();

	// Inherited via AccessibleControl
	virtual bool hasValue() override;
	virtual String getValue() override;
	virtual LONG getRole() override;
	virtual bool hasDefaultAction() override;
	virtual String getDefaultAction() override;
	virtual bool doDefaultAction() override;
	virtual bool hasKeyboardShortcut() override;
	virtual String getKeyboardShortcut() override;
	virtual void setValue(const String &) override;

private:
	LONG role;
};

#endif