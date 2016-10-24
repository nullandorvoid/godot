
#ifndef CONTROL_ACCESSIBLE_H
#define CONTROL_ACCESSIBLE_H

#include "accessibleCanvasItem.h"

class AccessibleControl : public AccessibleCanvasItem
{
public:
	AccessibleControl(Variant control, LONG defaultState);
	virtual ~AccessibleControl();

	virtual RECT getClientRectLocation();
	virtual void OnSignal(const String& signal);

	virtual bool canGetKeyFocus() override;
	virtual bool hasKeyFocus() override;
	virtual bool forceKeyFocus() override;
};

#endif