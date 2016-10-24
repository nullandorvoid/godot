#ifndef CONTROL_ACCESSIBLE_LABEL_H
#define CONTROL_ACCESSIBLE_LABEL_H

#include "accessibleControl.h"

class AccessibleLabel :	public AccessibleControl
{
public:
	AccessibleLabel(Variant label);
	virtual ~AccessibleLabel();

	// Inherited via AccessibleControl
	virtual String getName() override;
	virtual bool hasValue() override;
	virtual String getValue() override;
	virtual LONG getRole() override;
	virtual bool hasDefaultAction() override;
	virtual String getDefaultAction() override;
	virtual bool doDefaultAction() override;
	virtual bool hasKeyboardShortcut() override;
	virtual String getKeyboardShortcut() override;
	virtual void setValue(const String &) override;
};

#endif