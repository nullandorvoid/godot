#ifndef CONTROL_ACCESSIBLE_POPUP_H
#define CONTROL_ACCESSIBLE_POPUP_H

#include "accessibleControl.h"

class AccessiblePopup :	public AccessibleControl
{
public:
	AccessiblePopup(Variant popup);
	virtual ~AccessiblePopup();

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

	virtual void OnSignal(const String&) override;

private:
	void initializePopup();
	void endPopup();
	String getVisibilityReason();	
};

#endif
