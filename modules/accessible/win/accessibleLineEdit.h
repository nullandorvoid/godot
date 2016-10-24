#ifndef LINEEDIT_ACCESSIBLE_H
#define LINEEDIT_ACCESSIBLE_H

#include "accessibleControl.h"
class AccessibleLineEdit : public AccessibleControl
{
public:
	AccessibleLineEdit(Variant c);
	virtual ~AccessibleLineEdit();

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