#ifndef CONTROL_ACCESSIBLE_CANVAS_ITEM_H
#define CONTROL_ACCESSIBLE_CANVAS_ITEM_H

#include "accessibleBase.h"

class AccessibleCanvasItem : public AccessibleBase
{
public:
	AccessibleCanvasItem(Variant control, LONG defaultState);
	virtual ~AccessibleCanvasItem();

	virtual void OnSignal(const String& signal);

private:
	void setVisibility();
};

#endif