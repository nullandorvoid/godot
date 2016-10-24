#include "accessibleCanvasItem.h"
#include "print_string.h"

const char visibility[] = "visibility_changed";

AccessibleCanvasItem::AccessibleCanvasItem(Variant c, LONG defaultState)
	:AccessibleBase(c, defaultState)
{
	AddNotableSignal(visibility);
	setVisibility();
}

AccessibleCanvasItem::~AccessibleCanvasItem()
{
}

void AccessibleCanvasItem::setVisibility() {	
	AccessibleBase::setVisibility("godot_state", (bool)getNode().call("is_visible"));
}

void AccessibleCanvasItem::OnSignal(const String& signal) {
	AccessibleBase::OnSignal(signal);

	if (signal == visibility) {
		setVisibility();
	}
}