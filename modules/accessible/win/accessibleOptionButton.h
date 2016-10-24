#ifndef OPTIONBUTTON_ACCESSIBLE_H
#define OPTIONBUTTON_ACCESSIBLE_H

#include "accessibleButton.h"

class AccessibleOptionButton :	public AccessibleButton
{
public:
	AccessibleOptionButton(Variant control);
	virtual ~AccessibleOptionButton();

	virtual bool hasValue();
	virtual String getValue();

	virtual LONG getRole();

protected:
	virtual void setValue(const String&);
};

#endif

