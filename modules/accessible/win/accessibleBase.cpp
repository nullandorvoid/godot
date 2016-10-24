#include "print_string.h"

#include "accessibleBase.h"

#include "Util.h"

using namespace AccessibleHelpers;

AccessibleBase::AccessibleBase(Variant n, LONG defaultState)
{
	ID = -1;
	node = n;
	name = Util::GetUniqueName(node.call("get_name"));
	state = defaultState;

	forcingValue = false;
	forcingKeyboardShortcut = false;
}

AccessibleBase::~AccessibleBase()
{
}

void AccessibleBase::AddNotableSignal(const String& Signal)
{
	notableSignals.push_back(Signal);
}

void AccessibleBase::sendWinEvent(DWORD msg) {
	NotifyWinEvent(msg, GetActiveWindow(), OBJID_CLIENT, getId());
	//print_line(getFinalName() + String(" Win Event Triggered: ") + itos(msg));
}

#define SEND_SPECIAL_STATE(specialState, eventMessage) if ((oldstate & specialState) == 0 && (state & specialState) != 0) {stateNotification &= ~specialState;sendWinEvent(eventMessage);}
#define SEND_SPECIAL_STATE_CLEARED(specialState, eventMessage)if ((oldstate & specialState) != 0 && (state & specialState) == 0) {stateNotification &= ~specialState;sendWinEvent(eventMessage);}
void AccessibleBase::setState(LONG state) {
	LONG oldstate = this->state;
	this->state = state;

	LONG stateNotification = state ^ oldstate;
	if (stateNotification == 0) {
		return;
	}

	//If we set special states, don't send a general notification, but send a special one
	SEND_SPECIAL_STATE(STATE_SYSTEM_INVISIBLE, EVENT_OBJECT_HIDE);
	SEND_SPECIAL_STATE_CLEARED(STATE_SYSTEM_INVISIBLE, EVENT_OBJECT_SHOW)

	SEND_SPECIAL_STATE(STATE_SYSTEM_FOCUSED, EVENT_OBJECT_FOCUS);
	SEND_SPECIAL_STATE(STATE_SYSTEM_SELECTED, EVENT_OBJECT_SELECTION)

	//If either the state is set to zero or the state WASN'T set to zero, and at least one of the states
	//wasn't a special state, notify everyone
	if (stateNotification != 0) {
		sendWinEvent(EVENT_OBJECT_STATECHANGE);
	}
}

void AccessibleBase::addState(LONG state) {
	setState(getState() | state);
}

void AccessibleBase::removeState(LONG state) {
	setState(getState() & ~state);
}

String AccessibleBase::getName() { return name; }

RECT AccessibleBase::getScreenRectLocation()
{
	//Get the location within the client location
	RECT loc = getClientRectLocation();

	//Convert to screen space
	HWND hwnd = GetActiveWindow();
	ClientToScreen(hwnd, (LPPOINT)&loc.left);
	ClientToScreen(hwnd, (LPPOINT)&loc.right);

	//Return
	return loc;
}

void AccessibleBase::forceName(const String& val)
{
	forcingName = true;
	forcedName = val;
}

void AccessibleBase::clearForcedName()
{
	forcingName = false;
}

void AccessibleBase::forceValue(const String& val)
{
	forcingValue = true;
	forcedValue = val;
}

void AccessibleBase::clearForcedValue()
{
	forcingValue = false;
}

void AccessibleBase::forceKeyboardShortcut(const String& val)
{
	forcingKeyboardShortcut = true;
	forcedKeyboardShortcut = val;
}

void AccessibleBase::clearForcedKeyboardShortcut()
{
	forcingKeyboardShortcut = false;
}

void AccessibleBase::setUsingPopup(bool usingPopup)
{
	if (usingPopup)
		addState(STATE_SYSTEM_HASPOPUP);
	else
		removeState(STATE_SYSTEM_HASPOPUP);
}

void AccessibleBase::setVisibility(String reason, bool visible)
{
	visibilityController.set(reason, visible);
	
	if (visibilityController.get()) 
		removeState(STATE_SYSTEM_INVISIBLE);	
	else 
		addState(STATE_SYSTEM_INVISIBLE);	
}