#include "accessibleControl.h"

#include "print_string.h"

const char focus_enter[] = "focus_enter";
const char focus_exit[] = "focus_exit";
const char mouse_enter[] = "mouse_enter";
const char mouse_exit[] = "mouse_exit";

AccessibleControl::AccessibleControl(Variant c, LONG defaultState)
	:AccessibleCanvasItem(c, defaultState)
{
	AddNotableSignal(focus_enter);
	AddNotableSignal(focus_exit);
	AddNotableSignal(mouse_enter);
	AddNotableSignal(mouse_exit);
}


AccessibleControl::~AccessibleControl()
{
}

RECT AccessibleControl::getClientRectLocation()
{
	//Fetch the viewport's base rect and what it displays to determine how to scale and offset the rect for screen space
	Rect2 canvasRect = getNode().call("get_viewport").call("get_rect");
	Rect2 canvasVisibleRect = getNode().call("get_viewport").call("get_visible_rect");

	float xScale = canvasRect.size.x / (float)canvasVisibleRect.size.x;
	float yScale = canvasRect.size.y / (float)canvasVisibleRect.size.y;
	Vector2 offset = canvasRect.pos;

	//print_line("Scale: (" +rtos(xScale) + ", " + rtos(yScale) + ") -- Offset (" + rtos(canvasRect.pos.x) + ", " + rtos(canvasRect.pos.y) + ")");

	Rect2 grect = getNode().call("get_global_rect");

	grect.pos.x *= xScale;
	grect.pos.y *= yScale;
	grect.size.x *= xScale;
	grect.size.y *= yScale;
	grect.pos += offset;
	
	RECT wrect;
	wrect.left = grect.pos.x;
	wrect.right = grect.pos.x + grect.size.x;
	wrect.top = grect.pos.y;
	wrect.bottom = grect.pos.y + grect.size.y;

	return wrect;
}

bool AccessibleControl::canGetKeyFocus()
{
	return true;
}

bool AccessibleControl::hasKeyFocus()
{
	return (bool)getNode().call("has_focus");
}

bool AccessibleControl::forceKeyFocus()
{
	getNode().call("grab_focus");
	return true;
}

void AccessibleControl::OnSignal(const String& signal) {
	AccessibleCanvasItem::OnSignal(signal);

	if (signal == focus_enter) {	
		addState(STATE_SYSTEM_FOCUSED);
	}
	else if (signal == focus_exit) {
		removeState(STATE_SYSTEM_FOCUSED);
	}
	else if (signal == mouse_enter) {
		addState(STATE_SYSTEM_HOTTRACKED);
	}
	else if (signal == mouse_exit) {
		removeState(STATE_SYSTEM_HOTTRACKED);
	}
}
