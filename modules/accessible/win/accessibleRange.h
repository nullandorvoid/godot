#ifndef RANGE_ACCESSIBLE_H
#define RANGE_ACCESSIBLE_H

#include "accessibleControl.h"
class AccessibleRange :	public AccessibleControl
{
public:
	AccessibleRange(Variant control);
	virtual ~AccessibleRange();

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
};

#endif

